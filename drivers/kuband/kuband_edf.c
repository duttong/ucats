#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "kuband.h"

#define MAXBUF	1024
#define MAXVARS 80
#define WIDTH   20

typedef struct {
	char	var[WIDTH];
	char	format[WIDTH];
} edfstruct;

edfstruct Vars[MAXVARS];

float flow_M1 = 45.2;


/* reads variables from an .edf file
   and builds up varlst and fmtlst arrays */
int read_edf_files(char *files) {
	
	FILE 	*edffp;
	char	comm[50], buffer[200];
	char	var[WIDTH], varf[WIDTH];
	char	*file;
	short int varcount=0, num;

	/* open file */
	file = strtok(files, ";");
	while(file != NULL) {
		if ((edffp = fopen(file , "r")) == NULL) {
			sprintf(comm, "Missing file %s ", file );
			perror(comm);
		}
	
		/* parse variables from .edf file */
		while( fgets( buffer, 100, edffp ) != NULL ) {
			num = -1;
			sscanf(buffer, "%d %s %s", &num, var, varf);
			if (num != -1) {
				strcpy(Vars[varcount].var, var);
				strcpy(Vars[varcount].format, varf);
				varcount++;
			}
		}
		
		fclose(edffp);
		file = strtok(NULL, ";");
	}
	
	return varcount;

}

void send2link() {

	//char *p1, *p2;
	

}

void main() {
	
	unsigned int numvars = 0, i=0;
	char ttt[] = "flow_M1";

	numvars = read_edf_files("eng1.edf;eng2.edf;h2odata.edf;o3data.edf;");
	
	send2link();
	
	for(i=0; i<numvars; i++) {
		//printf("%s, %s, %f\n", Vars[i].var, Vars[i].format, &Vars[i].var);
	}
	printf("val = %d\n", &ttt);
	printf("numvars = %d\n", numvars);
	
}	