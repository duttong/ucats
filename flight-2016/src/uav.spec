SUBDIRS = 
tmcbase = base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc 
tmcbase = valco.tmc ozone.tmc maycomm.tmc vaisala.tmc
cmdbase = valves.c commands.c uav.cmd uav.slp
SCRIPT = Experiment.config VERSION rungc cleanup crunch.sh snafuEXT
SCRIPT = interact interact.ser uav.slp normal.cfg hardware.cfg null.sh
TGTDIR = $(TGTNODE)/home/uav/flight
SRC = gcitx.h regnames.h valves.h addresses.h adr2000.h elec.h maycomm.h
SRC = o3ser.h smart.h vaisala.h reveal.h nasdat.h kuband.h
DISTRIB = scr.cfg
uavcol  : basecol.tmc
uavdoit : uav.doit
caldoit : cal.doit
labdoit : lab.doit
serdoit : ser.doit
playdoit : play.doit
uavdisp : integrate.c int.tmc intdsp.tmc bittxt.tmc plot.tmg main.tbl h2o.tbl
uavalgo : integrate.c int.tmc intdsp.tmc reveal.c nasdat.c kusend.c uav.tma
labalgo : integrate.c int.tmc intdsp.tmc reveal.c nasdat.c kusend.c lab.tma
calalgo : valves.c cal.tma
uav.sft : uav.slp uav.sol
eng1ext : eng1.edf
eng2ext : eng2.edf
o3ext   : o3data.edf
o3xext  : o3xdata.edf
h2oext  : h2odata.edf
gcitxext : gcitx.c gcitx.tmc
intext  : integrate.c int.tmc intres.tmc
NOSUBBUS
%%
MODEL=l
CPU=-2
OPTIM=-N8k
uavdoit : main.fld h2o.fld normal.cfg
caldoit : main.fld h2o.fld normal.cfg
labdoit : main.fld h2o.fld normal.cfg
playdoit : main.fld h2o.fld normal.cfg
serdoit : main.fld h2o.fld normal.cfg
addresses.h : uavcol.c
addresses.h : uavcmd.c
uavsrvr.o : addresses.h
uavcol : addresses.h 
