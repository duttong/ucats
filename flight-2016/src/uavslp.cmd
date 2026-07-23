%{
  #ifdef SERVER
	#define SERVER_INIT
	void cis_initialize(void) {
	  int ret = 0;
	  ret |= solp_init(SOLDRV_PROXY_A, 1, "gsv channel 1 Inject\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 2, "gsv channel 1 Load\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 3, "flow main channel 1 100\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 4, "flow main channel 1 60\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 5, "flow main channel 1 60\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 6, "flow main channel 1 60\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 7, "flow main channel 1 60\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 8, "flow main channel 1 50\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 9, "flow backflush channel 1 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 10, "flow backflush channel 1 35\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 11, "flow backflush channel 1 35\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 12, "flow backflush channel 1 35\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 13, "flow backflush channel 1 35\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 14, "Press channel 1 Setpoint 12\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 15, "Press channel 1 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 16, "Press channel 1 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 17, "Press channel 1 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 18, "Press channel 1 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 19, "gsv channel 2 Inject\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 20, "gsv channel 2 Load\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 21, "flow main channel 2 55\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 22, "flow main channel 2 55\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 23, "flow main channel 2 55\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 24, "flow main channel 2 55\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 25, "flow main channel 2 55\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 26, "flow backflush channel 2 30\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 27, "flow backflush channel 2 47\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 28, "flow backflush channel 2 47\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 29, "flow backflush channel 2 47\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 30, "flow backflush channel 2 47\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 31, "Press channel 2 Setpoint 12\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 32, "Press channel 2 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 33, "Press channel 2 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 34, "Press channel 2 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 35, "Press channel 2 Setpoint 20\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 36, "elec bias 1 90\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 37, "elec bias NULL\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 38, "elec bias 2 100\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 39, "elec bias 2 010\n");
	  ret |= solp_init(SOLDRV_PROXY_A, 40, "elec bias NULL\n");
	  if (ret) exit(1);
	}
	void cis_terminate(void) {
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 1);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 2);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 3);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 4);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 5);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 6);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 7);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 8);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 9);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 10);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 11);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 12);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 13);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 14);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 15);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 16);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 17);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 18);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 19);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 20);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 21);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 22);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 23);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 24);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 25);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 26);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 27);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 28);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 29);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 30);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 31);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 32);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 33);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 34);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 35);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 36);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 37);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 38);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 39);
	  Soldrv_reset_proxy(SOLDRV_PROXY_A, 40);
	}
  #endif
%}
