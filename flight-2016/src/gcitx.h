/* gcitx.h */
void itx_new_inj( int fno, int injno );
void itx_new_inj_flnm( int fno, int injno, char *hd, long int T );
void itx_end_inj( void );
void itx_aux_data( char *t1, char *t2 );
void itx_aux_data_init( unsigned long Sec, long int T, char *SP );
void itx_ctr_dataF( float ctr );
void itx_ctr_dataUL(unsigned long  ctr );
void itx_ctr_dataL(long  ctr );
void itx_text_data( char *text );

