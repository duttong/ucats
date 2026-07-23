#define BUFFSIZE	500

#define	STX		2
#define ETX		3
#define	ACK		6
#define	ASC0	48

#define	SEC		1000000			// microsecs in a sec
#define	MAXDET		 8			// maximum number of detectors (addresses 0 to F), set lower to save memory
#define MAXPOINTS	16			// maximum number of data point received from electrometer
#define NOELECDATA			-999

typedef enum {
	FALSE = 0,
	TRUE
} bool;

typedef struct {
	int		numpnts;
	long	resp[MAXPOINTS];
} chrom_packet;

chrom_packet chrom[MAXDET];

int open_port();
void parse_chrom();

void send_command(int detnum, char *cmd);

void usage();
void print_chrom(int detnum);

void send_reset( int det );
void send_ADCresets( int det ); 

char *init_opt(int argc, char ** argv);
int init_smart();
int change_dac(int det,int setpoint);
int poll_electrometer( );
int read_electrometer( int det_num );
