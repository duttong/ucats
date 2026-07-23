#define BUFFSIZE	500

#define	STX		2
#define ETX		3
#define	ACK		6

#define	SEC		1000000		// microsecs in a sec
#define	MAXDET		16			// maximum number of detectors
#define MAXPOINTS	16			// maximum number of data point received from electrometer

//#define WAITFORREAD	usleep(SEC/10)

typedef enum {
	FALSE = 0,
	TRUE
} bool;

typedef struct {
	int	numpnts;
	double	resp[MAXPOINTS];
} chrom_packet;


char 	buffer[BUFFSIZE];					/* Data read from serial port */


chrom_packet chrom[MAXDET];



int open_port(char *port);
int parse_chrom(char *buff);

void send_command(int fd, int detnum, char *cmd);
char * read_port(int fd);

void clearbuffer();
void usage();
void print_chrom(int detnum);

