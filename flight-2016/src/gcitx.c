#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "gcitx.h"
#include "nortlib.h"
/* STILL Needed:
   library functions for hms(T) and myd(T)
*/

#define NUMITXCOLS  2

#define hms(x) "00:00:00"
#define mdy(x) "01-01-1996"
#define MAX_AUX_STR 200
static char itx_aux_str[MAX_AUX_STR];
static int itx_aux_len;
static FILE *itx_file = NULL;
static int itx_fno, itx_injno;


void itx_end_inj( void ) {
  int i;
  
  if ( itx_file != 0 ) {
	/* write the end of the last injection, together with
	   the auxiliary data string
	*/
	fprintf( itx_file, "END\n" );
	for (i = 1; i <= NUMITXCOLS; i++ ) {
	  fprintf( itx_file, "X note chr%d_%05d, \" %d; %s",
				i, itx_injno, i, itx_aux_str );
	}
	fprintf( itx_file, "%s", "X SetScale /P x, 0, 0.1" );
	for ( i = 1; i <= NUMITXCOLS; i++ )
	  fprintf( itx_file, ", chr%d_%05d", i, itx_injno );
	fprintf( itx_file, "\n" );
  }
}

void itx_new_inj( int fno, int injno ) {
  int i;

  itx_end_inj( );
  if ( itx_file == 0 ) {
	/* Only true the very first time */
	atexit( itx_end_inj );
  } else if ( fno != itx_fno ) {
	fclose( itx_file );
	itx_file = 0;
  }
  if ( itx_file == 0 ) {
	char fname[80];
	sprintf( fname, "gc%d.itx", fno );
	if ((itx_file = fopen( fname, "w" )) == NULL)
		printf ("=====Cannot open %s\n", fname);	
	if ( itx_file == 0 )
	  nl_error( 3, "Unable to open output file %s", fname );
	fprintf( itx_file, "IGOR\n" );
  }
  fprintf( itx_file, "WAVES " );
  for ( i = 1; ; ) {
	fprintf( itx_file, "chr%d_%05d", i, injno );
	if ( i++ == NUMITXCOLS ) break;
	fprintf( itx_file, ", " );
  }
  fprintf( itx_file, "\nBEGIN\n" );
  itx_injno = injno;
}

/* uses full name convention */
void itx_new_inj_flnm( int fno, int injno, char *hd, long int T ) {
  int i;
  char  *path = "chroms";
  struct tm *tmbuf;
  struct stat buf;

  itx_end_inj( );
  if ( itx_file == 0 ) {
	/* Only true the very first time */
	atexit( itx_end_inj );
  } else if ( fno != itx_fno ) {
	fclose( itx_file );
	itx_file = 0;
  }
  if ( itx_file == 0 ) {
	char fname[80];

	tmbuf = localtime( &T );

	/* make path dir if needed */
	if ( stat( path, &buf ) != 0 ) {
		mkdir ( path, S_IRWXU | S_IRWXG | S_IREAD );
	}

	sprintf( fname, "%s/%s%04d%02d%02d_%02d%02d%02d.itx", path, hd, 
		tmbuf->tm_year + 1900, tmbuf->tm_mon+1, tmbuf->tm_mday,
		tmbuf->tm_hour, tmbuf->tm_min, tmbuf->tm_sec );

	if ((itx_file = fopen( fname, "w" )) == NULL)
		printf ("=====Cannot open %s\n", fname);	
	if ( itx_file == 0 )
	  nl_error( 3, "Unable to open output file %s", fname );
	fprintf( itx_file, "IGOR\n" );
  }
  fprintf( itx_file, "WAVES " );
  for ( i = 1; ; ) {
	fprintf( itx_file, "chr%d_%05d", i, injno );
	if ( i++ == NUMITXCOLS ) break;
	fprintf( itx_file, ", " );
  }
  fprintf( itx_file, "\nBEGIN\n" );
  itx_injno = injno;
}



/* append additional string(s) to the itx_aux_string */
void itx_aux_data( char *t1, char *t2 ) {
  int l1, l2;
  l1 = strlen(t1);
  l2 = strlen(t2);
  assert( itx_aux_len + l1 + l2 < MAX_AUX_STR-1 );
  strcpy( itx_aux_str + itx_aux_len, t1 );
  strcpy( itx_aux_str + itx_aux_len + l1, t2 );
  itx_aux_len += l1 + l2;
}

/* initialize the itx_aux_string */
void itx_aux_data_init( unsigned long Sec, long int T, char *SP ) {
  struct tm *tmbuf;
  char tstr[12];

  sprintf( itx_aux_str, "%ld; ", Sec );
  itx_aux_len = strlen( itx_aux_str );
  tmbuf = localtime( &T );
  sprintf( tstr, "%02d:%02d:%02d", tmbuf->tm_hour, tmbuf->tm_min,
	tmbuf->tm_sec );
  itx_aux_data( tstr, "; " );
  sprintf( tstr, "%02d-%02d-%04d", tmbuf->tm_mon+1, tmbuf->tm_mday,
	tmbuf->tm_year + 1900 );
  itx_aux_data( tstr, "; " );
  itx_aux_data( SP, "; " );
}

void itx_ctr_dataF( float ctr ) {
	if ( itx_file == NULL )
		return;
	fprintf( itx_file, " %f",ctr);
}

void itx_ctr_dataL( long ctr ) {
	if ( itx_file == NULL )
		return;
	fprintf( itx_file, " %ld",ctr);
}

void itx_ctr_dataUL( unsigned long ctr ) {
	if ( itx_file == NULL )
		return;
	fprintf( itx_file, " %lu", ctr );
}

void itx_text_data( char *text ) {
	if ( itx_file == NULL )
		return;
	fprintf( itx_file, "%s", text );
}
