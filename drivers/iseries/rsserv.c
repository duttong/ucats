#include <unistd.h>
#include <fcntl.h>
#include <sys/dev.h>
#include <sys/name.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "/usr/local/include/nortlib.h"
#include "/usr/local/include/collect.h"
#include "rsserv.h"

#define TIMEOUT_PERIOD	10
#define RCV_MSG_SIZE	256
#define	RS_DATA_SIZE	20

#define ACK				6
#define QUEUE_SIZE		10

enum {
	err_timeout
};

enum {
	com_noCom,
	com_readTemp,
	com_changeSp
};

typedef struct {
	char 		addrStr[4];
	int 		decPoint;
	char 		addr;
} AddrStruct;

typedef struct {
	AddrStruct	* addrList;
	float		* omegaList;
	int			numAddrs;
} AddrInfo;

typedef enum {
	FALSE = 0,
	TRUE
} Bool;

/** Begin Global Variable Declarations **/
char	
		str_readTemps[] = {"00"},
		str_readSP1[] = {"0100"},
		str_readDp[] = {"0324"},
		str_changeSp1[] = {"0200"},
		str_changeSp2[] = {"0201"},
		etx[] = { 03, '\0' },
		stx[] = { 02, '\0' };

char	rsPort[PATH_MAX+1] = {"/dev/ser1"};

char	QueueArray[QUEUE_SIZE][RCV_MSG_SIZE];
pid_t	pidArray[QUEUE_SIZE];

float 	errCode[] = {1000.0};


struct {
	int in;
	int out;
	int numElements;
} Queue;
/** End Global Variable Declarations **/




void Init_queue ()
{
	Queue.in = -1;
	Queue.out = -1;
	Queue.numElements = 0;

	return;
}

int Enqueue 
(
	char 			* msg,
	pid_t			pid
)
{


	if (Queue.numElements == QUEUE_SIZE)
		return -1;

	Queue.in++;
	Queue.numElements++;
	if (Queue.out == -1)
		Queue.out++;

	if (Queue.in == QUEUE_SIZE)
		Queue.in = 0;

	strcpy (QueueArray[Queue.in], msg);
	pidArray[Queue.in] = pid;
	

#ifdef DEBUG
printf ("-----------------------------------element %s enqueued\n", msg);
printf ("-----------------------------------Queue.in = %d\n", Queue.in);
#endif
	return 0;
}

pid_t Dequeue (char * msg)
{
	int				temp;
	pid_t			thePid;



	if (Queue.numElements == 0) {
		msg[0] = com_noCom;
		msg[1] = '\0';
		return -1;
	}

	temp = Queue.out;
	Queue.out++;
	Queue.numElements--;

	if (Queue.numElements == 0)
		Queue.in = Queue.out = -1;

	if (Queue.out == QUEUE_SIZE)
		Queue.out = 0;

#ifdef DEBUG
printf ("***********************************element %s dequeued\n", QueueArray[temp]);
printf ("***********************************Queue.out = %d\n", temp );
printf ("***********************************numElements = %d\n", Queue.numElements);
#endif
	strcpy (msg, QueueArray[temp]);
	thePid = pidArray[temp];
	return thePid;
	
}


Bool Is_hex
(
	char		* addr
)
{
	char		* c;

	c = addr;

	while (*c != '\0') {
		*c = toupper (*c);
		if (((*c < '0') || (*c > '9')) 
			&& ((*c < 'A') || (*c > 'F')))
			return FALSE;
		c++;
	}

	return TRUE;
}

void Send_arbitrary_comm 
(
	int				netId,
	char			* addr,
	char			* command
)
{
	char			msg[RCV_MSG_SIZE];

	strcpy (msg, stx);
	strcat (msg, addr);
	strcat (msg, command);
	add_checksum (msg);
	strcat (msg, etx);

	write (netId, msg, strlen (msg));

	return;
}


Bool Verify_addr
/*
 * checks to see if a string is a valid address string, and
 * converts address strings to Omega address strings.
 */
(
	char		* addr,
	char		* newAddr
)
{
	switch (strlen (addr)) {
		case 0 :
			return FALSE;
			
		case 1 :
			strcpy (newAddr, "L0");
			strcat (newAddr, addr);
			break;
			
		case 2 :
			strcpy (newAddr, "L");
			strcat (newAddr, addr);
			break;
			
		case 3 :
			switch (addr[0]) {
				case '0' :
					strcpy (newAddr, addr);
					newAddr[0] = 'L';
					break;
				
				case '1' :
					strcpy (newAddr, addr);
					newAddr[0] = 'L';
					break;
					
				default :
					return FALSE;
					break;
			}
			break;
			
		default :
			return FALSE;
	}
	return TRUE;
}

Bool Server_init_addrs
(
	char		* addrStr,
	AddrInfo	* rsAddrs
)
{
	int			i,
				addrLen,
				commaCount;
				
	char		* addr;
	
	AddrStruct	* currentAddr;
	
	float		* currentVal;

	addr = addrStr;
	commaCount = 0;
	
	while (*addr != NULL) {
		commaCount += (*addr == ',');
		addr++;
	}

	commaCount++;
	rsAddrs->numAddrs = commaCount;

	rsAddrs->omegaList = (float *) malloc (sizeof (float) * commaCount * 2);
	rsAddrs->addrList = (AddrStruct *) malloc (sizeof (AddrStruct) * (commaCount));

	currentAddr = rsAddrs->addrList;

	addr = strtok (addrStr, ",");

	while (addr != '\0') {
		addrLen = strlen (addr);

		if (!Is_hex (addr)) {
			free (rsAddrs->addrList);
			free (rsAddrs->omegaList);
			
			/* !! MEMO !! */

#ifdef DEBUG
			printf ("Non-hex address in address string:  %s\n", addr);
#endif
			
			return FALSE;
		}

		if (Verify_addr (addr, currentAddr->addrStr) == FALSE) {
			/* !! MEMO !! */

#ifdef DEBUG
			printf ("Bad address in address string:  %s\n", addr);
#endif

			return FALSE;
		}

		currentAddr++;
		addr = strtok (NULL, ",");
	}
	return TRUE;
}

int Server_init_options
(
	int 		argc,
	char		** argv,
	AddrInfo	* rsAddrs
)
{
	int 		c,
				errflag = 0;
	pid_t		server_id,
				quit_proxy;
	char		q[] = {msg_quit, '\0'};
	char		t[] = {msg_test, 'T', 'e', 's', 't', '\0'};


	while ( (c = getopt (argc, argv, "tqa:p:") ) != -1) {
		switch (c) {
			case 't' :
				server_id = qnx_name_locate (0, "/rs485/server", 0, NULL);
				if (server_id == -1) {
					printf ("can't find server\m");
					return -1;
				}
				
				quit_proxy = qnx_proxy_attach (server_id, t, 2, -1);
				Trigger (quit_proxy);
				qnx_proxy_detach (quit_proxy);
				return -1;
			case 'q' : 
				server_id = qnx_name_locate (0, "/rs485/server", 0, NULL);
				if (server_id == -1) {
					printf ("can't find server\m");
					return -1;
				}
				
				quit_proxy = qnx_proxy_attach (server_id, q, 2, -1);
				Trigger (quit_proxy);
				qnx_proxy_detach (quit_proxy);
				return -1;
			break;
				
			case 'a' : 
				if (Server_init_addrs (optarg, rsAddrs) == FALSE)
					return -1;
				break;

			case 'p' :
				strcpy (rsPort, optarg);
				break;

			case '?' :
				errflag++;
				break;
		}
	}
	if (errflag)
		return -1;
	return 0;
}

Bool Verify_omegas 
(
	int			rsNetId,
	AddrInfo	* rsAddrs
)
{
	int			i,
				n,
				bytesRead;

	char		buf[RCV_MSG_SIZE];
	char		* bufPtr;
	
	for (i = 0; i < rsAddrs->numAddrs; i++) {
		bufPtr = buf;
		bytesRead = 0;
		Send_arbitrary_comm (rsNetId, rsAddrs->addrList[i].addrStr, str_readDp);
		n = dev_read (rsNetId, bufPtr, RCV_MSG_SIZE, 1, 0, TIMEOUT_PERIOD, 0, 0);
		bytesRead += n;
		bufPtr = &buf[bytesRead];
		while (( n > 0) && (buf[bytesRead - 1] != ACK)) {
			n = dev_read (rsNetId, bufPtr, RCV_MSG_SIZE, 1, 0, TIMEOUT_PERIOD, 0, 0);
			bytesRead += n;
			bufPtr = &buf[bytesRead];
		}

		if (n == 0) {

#ifdef DEBUG
		printf ("Could not find omega %s on the RS485 network.\n",
			rsAddrs->addrList[i].addrStr);
#endif
			rsAddrs->addrList[i].decPoint = 1;
		} else {

#ifdef DEBUG
printf (" found.  decPoint = %d\n", buf[5]-'0');
#endif

			if (buf[bytesRead - 1] == ACK)
				rsAddrs->addrList[i].decPoint = buf[5] - '0';
				/*
				buf[bytesRead] = '\0';
				printf ("buf %s\n", buf);
				*/
		}
	}
	return TRUE;
}

void add_checksum
(
    char 	* the_msg
)
{
    char 	low_byte[3];
    int		checksum,
		i,
		length;


    length = strlen (the_msg);
    checksum = 0;

    for (i = 2; i < length; i++)
        checksum = checksum + the_msg[i];

    low_byte[0] = checksum & 0xF0;
    low_byte[0] = low_byte[0] / 16 + 48;

    low_byte[1] = checksum & 0x0F;
    low_byte[1] = low_byte[1] + 48;

    low_byte[2] = '\0';

    for (i = 0; i < 2; i++)
    {
        if (low_byte[i] > 57)
            low_byte[i] = low_byte[i] + 7;
    }

    strcat (the_msg, low_byte);

    return;
}

void Send_rs_msg
(
    char 	* which_address,
    char	* what_msg,
	int		fd
)
{
    char 	msg_to_send[32];
    strcpy (msg_to_send, stx);
    strcat (msg_to_send, which_address);
    strcat (msg_to_send, what_msg);
    add_checksum (msg_to_send);
    strcat (msg_to_send, etx);

    write (fd, msg_to_send, strlen (msg_to_send));



    return;
}


float Decode_sp
(
    char	* rs485_msg,
    int		size,
	float	decimal
)
{
    int		sign = 1,
    		i;

	float	ret_value;
    char	value[5];

	if (rs485_msg[0] == 'E')
		return errCode[rs485_msg[1]];

    if (size < 10)
    	return -1;

	decimal = pow (0.1, decimal);

    
    for (i = 6; i < 10; i++)
    {
        value[i-6] = rs485_msg[i];
    }
    
    value[4] = '\0';
    
	if ((rs485_msg[4] + rs485_msg[5]) != ('0' + '0')) sign = -1;


/*    
    ret_value = sign * (atof (value)) * decimal;
*/
    ret_value = sign * (atof (value));
/*
    printf ("decoded value %s = %f\n", value, (float) ret_value);
 */   
    return (ret_value);
}

float Decode_temp
(
    char	* rs485_msg,
    int		size,
	float		decimal
)
{
    int		sign = 1,
    		i;

	float	ret_value;
    char	value[5];

	if (rs485_msg[0] == 'E')
		return errCode[rs485_msg[1]];

    if (size < 12)
    	return -1;

	decimal = pow (0.1, decimal);

    
    for (i = 8; i < 12; i++)
    {
        value[i-8] = rs485_msg[i];
    }
    
    value[4] = '\0';
    
	if ((rs485_msg[7] & 0X01) == 1) sign = -1;

/*    
    ret_value = sign * (atof (value)) * decimal;
*/
    ret_value = sign * (atof (value));
/*
    printf ("decoded value %s = %f\n", value, (float) ret_value);
 */   
    return (ret_value);
}

void main
(
	int argc,
	int ** argv
)
{
	AddrInfo	rsAddrs;

	char		rcvMsg[RCV_MSG_SIZE],
				rsData[RS_DATA_SIZE],
				commBuf[RS_DATA_SIZE],
				signChar,
				* msgPtr;
	
	pid_t		rcvPid,
				rsProxy,
				colProxy;
			
	send_id		colId;
			
	int			rsNetId,
				serverNameId,
				dataLen = 0,
				currentAddr = 0,
				rsCommand,
				n;
			
	Bool		rsDataPending = FALSE;
	Bool		readSP1Flag = FALSE;
	
	
	
	
	Init_queue();
	rsAddrs.numAddrs = 0;
	
	if (Server_init_options (argc, argv, &rsAddrs) == -1)
		return;

	if (rsAddrs.numAddrs < 1) {
		printf ("Omega address list required (e.g. -a C1,C2,C3,C4)\n");
		return;
	}
	if ((serverNameId = qnx_name_attach (0, "/rs485/server")) == -1) {
		perror ("Could not run server");
		/* !!MEMO!! */
		return;
	}
	
	if ((rsNetId = open (rsPort, O_RDWR)) == -1) {
		perror ("Could not open RS485 network");
		return;
	}

	/* clear the net */
	n = dev_read (rsNetId, rsData, RS_DATA_SIZE, 1, 0, TIMEOUT_PERIOD, 0, 0);
	
	Verify_omegas (rsNetId, &rsAddrs);
	colId = Col_send_init ("RS485_data", rsAddrs.omegaList, sizeof (float) * rsAddrs.numAddrs * 2);
	colProxy = Col_set_proxy (3, msg_colId);
	
	if ((rsProxy = qnx_proxy_attach (0, 0, 0, -1)) == -1) {
		perror ("Unable to attach proxy");
		close (rsNetId);
		return;
	}
	
	rcvMsg[0] = msg_noMsg;
	rcvMsg[0] = '\0';
	
	while (rcvMsg[0] != msg_quit) {


		/* Receive() block and wait for incoming messages */
		rcvPid = Receive (0, rcvMsg, RCV_MSG_SIZE);
		if (rcvPid == rsProxy) {
			/* Receive()'d proxy from RS485 - read and process available data */
			/* ??? Do we need a TIMEOUT_PERIOD here ??? */
			n = dev_read (rsNetId, &rsData[dataLen], RS_DATA_SIZE-dataLen, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
			if (n > 0)  {
				/* data has been read - process it */
				dataLen = dataLen + n;
			} else {
				/* no data is available - a timeout has occured */
				/* close and reopen rs485 network, and read next address */
				dataLen = 3;
				rsData[0] = 'E';
				rsData[1] = err_timeout;
				rsData[2] = ACK; 
				rsDataPending = FALSE;
				qnx_proxy_detach (rsProxy);
				close (rsNetId);
				rsNetId = open (rsPort, O_RDWR);
				rsProxy = qnx_proxy_attach (0, 0, 0, -1);
				if (rsProxy == -1)  {
					/* !!MEMO!! */
					close (rsNetId);
				}
			}
			if (rsData[dataLen-1] == ACK) {
				rsData[dataLen] = '\0';
				rsDataPending = FALSE;
				if (rsCommand == com_readTemp) {
					if (readSP1Flag == TRUE) {
						rsAddrs.omegaList[currentAddr*2+1] = Decode_sp (rsData, dataLen,
							(float) rsAddrs.addrList[currentAddr].decPoint);
						readSP1Flag = FALSE;
						if (currentAddr == rsAddrs.numAddrs-1) {
							rsDataPending = FALSE;
							Col_send (colId);
							currentAddr = 0;
						} else {
							currentAddr++;
							Send_rs_msg (rsAddrs.addrList[currentAddr].addrStr, str_readTemps, rsNetId);
							n = dev_read (rsNetId, rsData, 0, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
							rsDataPending = TRUE;
						}
					}
					else {
						rsAddrs.omegaList[currentAddr*2] = Decode_temp (rsData, dataLen,
							(float) rsAddrs.addrList[currentAddr].decPoint);
						Send_rs_msg (rsAddrs.addrList[currentAddr].addrStr, str_readSP1, rsNetId);
						n = dev_read (rsNetId, rsData, 0, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
						rsDataPending = TRUE;
						readSP1Flag = TRUE;
					}
				}
				dataLen = 0;
			}
		}
		
		if (rsDataPending == FALSE)  {
/* printf ("checking msg\n"); */
			/* No data is pending to be read from rs485 - Enqueue the current message */
			/* and Dequeue the next message to be processed. */
			if (Queue.numElements > 0)  {
				if (rcvPid != rsProxy)
					Enqueue (rcvMsg, rcvPid);
				rcvPid = Dequeue (rcvMsg);
			}
			switch (rcvMsg[0]) {
				case msg_colId :
					/* Collection has requested temperatures */
					rcvMsg[1] = '\0';
					rsCommand = com_readTemp;
					if (currentAddr == 0) {
						/* Don't start reading if we are already in the middle of reading temps. */
						Send_rs_msg (rsAddrs.addrList[currentAddr].addrStr, str_readTemps, rsNetId);
						/* arm the rs485 proxy */
						n = dev_read (rsNetId, rsData, 0, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
						rsDataPending = TRUE;
					}
				break;

				case msg_changeSp1 :
					/* Collection has requested temperatures */
					rsCommand = com_changeSp;
					rcvMsg[4] = '\0';
					if (rcvMsg[5] == '-') {
						signChar = '1';
						msgPtr = &rcvMsg[6];
					} else {
						signChar = '0';
						msgPtr = &rcvMsg[5];
					}
					strcpy (commBuf, str_changeSp1);
					strcat (commBuf, msgPtr);
					commBuf[8] = commBuf[9] = signChar;
					Send_rs_msg (&rcvMsg[1],commBuf, rsNetId);
					n = dev_read (rsNetId, rsData, 0, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
					rsDataPending = TRUE;
	
				case msg_changeSp2 :
					/* Collection has requested temperatures */
					rsCommand = com_changeSp;
					rcvMsg[4] = '\0';
					if (rcvMsg[5] == '-') {
						signChar = '1';
						msgPtr = &rcvMsg[6];
					} else {
						signChar = '0';
						msgPtr = &rcvMsg[5];
					}
					strcpy (commBuf, str_changeSp2);
					strcat (commBuf, msgPtr);
					commBuf[8] = commBuf[9] = signChar;
					Send_rs_msg (&rcvMsg[1],commBuf, rsNetId);
					n = dev_read (rsNetId, rsData, 0, 1, 0, TIMEOUT_PERIOD, rsProxy, 0);
					rsDataPending = TRUE;
				break;

			break;

				default: break;
			}
		} else if (rcvPid != rsProxy) {
			/* Data is pending to be read from rs485 - enqueue message if it is not an rsProxy */
			Enqueue (rcvMsg, rcvPid);
		}
	}
	qnx_proxy_detach (rsProxy);
	close (rsNetId);
	/* qnx_name_detach (serverNameId); */
	/* do any other shutdown stuff here */
}
