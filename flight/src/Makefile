# Makefile Generated Sat Feb 04 17:04:04 gmt 2023
MNC=uav
HOMEDIR=/home/uav/flight/src
SPECFILE=uav.spec
SRC=gcitx.h regnames.h valves.h addresses.h adr2000.h elec.h
SRC+=maycomm.h o3ser.h smart.h vaisala.h reveal.h nasdat.h kuband.h
SRC+=base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc
SRC+=valco.tmc ozone.tmc maycomm.tmc vaisala.tmc basecol.tmc uav.doit
SRC+=dc8.doit cal.doit lab.doit ser.doit play.doit integrate.c
SRC+=int.tmc intdsp.tmc bittxt.tmc plot.tmg main.tbl h2o.tbl reveal.c
SRC+=nasdat.c kusend.c commands.c uav.tma lab.tma valves.c cal.tma
SRC+=uav.slp uav.sol eng1.edf eng2.edf o3data.edf o3xdata.edf
SRC+=h2odata.edf gcitx.c gcitx.tmc intres.tmc uav.cmd
TOOL=uav.spec Makefile
SCRIPT=Experiment.config VERSION rungc cleanup crunch.sh snafuEXT
SCRIPT+=interact interact.ser uav.slp normal.cfg hardware.cfg null.sh
OBJ=uavcol.c uav.pcm tm.dac uavcoloui.c uavcol.o uavcoloui.o
OBJ+=main.fld h2o.fld uavdisp.tmc uavdisptmg.tmc uavdisp.c
OBJ+=uavdispoui.c uavdisp.o integrate.o uavdispoui.o uavalgoa.tmc
OBJ+=uavalgo.c uavalgooui.c uavalgo.o reveal.o nasdat.o kusend.o
OBJ+=commands.o uavalgooui.o labalgoa.tmc labalgo.c labalgooui.c
OBJ+=labalgo.o labalgooui.o calalgoa.tmc calalgo.c calalgooui.c
OBJ+=calalgo.o valves.o calalgooui.o uavslp.sol eng1extedf.oui
OBJ+=eng1ext.tmc eng1ext.c eng1extoui.c eng1ext.o eng1extoui.o
OBJ+=eng2extedf.oui eng2ext.tmc eng2ext.c eng2extoui.c eng2ext.o
OBJ+=eng2extoui.o o3extedf.oui o3dataext.tmc o3ext.c o3extoui.c
OBJ+=o3ext.o o3extoui.o o3xextedf.oui o3xdataext.tmc o3xext.c
OBJ+=o3xextoui.c o3xext.o o3xextoui.o h2oextedf.oui h2odataext.tmc
OBJ+=h2oext.c h2oextoui.c h2oext.o h2oextoui.o gcitxext.c
OBJ+=gcitxextoui.c gcitxext.o gcitx.o gcitxextoui.o intext.c
OBJ+=intextoui.c intext.o intextoui.o uavslp.cmd uavcmd.c uavcmd.dat
OBJ+=uavclt.o uavcltoui.c uavcltoui.o uavsrvr.o uavsrvroui.c
OBJ+=uavsrvroui.o
TGT=uavcol uavdoit dc8doit caldoit labdoit serdoit playdoit uavdisp
TGT+=uavalgo labalgo calalgo uav.sft eng1ext eng2ext o3ext o3xext
TGT+=h2oext gcitxext intext uavclt uavsrvr
DISTRIB=scr.cfg uav.tma lab.tma cal.tma uav.sol base.tmc adr2000.tmc
DISTRIB+=gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc
DISTRIB+=maycomm.tmc vaisala.tmc uav.pcm tm.dac main.fld h2o.fld
NONRCS=
TMCBASE=base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc
TMCBASE+=valco.tmc ozone.tmc maycomm.tmc vaisala.tmc
CMDBASE=valves.c commands.c uav.cmd uav.slp
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/uav/flight
include /usr/local/lib/src/appgen.mk

all : $(TGT)
distribution : $(DSTRB)
	distribute $(TGTDIR) $(DSTRB); :

uavcol : uavcol.o uavcoloui.o
	$(LINK.priv) uavcol.o uavcoloui.o
	$(OUIUSE) uavcoloui.c
	promote uavcol
uavdoit : uav.doit
	mkdoit2 -o uavdoit  uav.doit && chmod a+x uavdoit
dc8doit : dc8.doit
	mkdoit2 -o dc8doit  dc8.doit && chmod a+x dc8doit
caldoit : cal.doit
	mkdoit2 -o caldoit  cal.doit && chmod a+x caldoit
labdoit : lab.doit
	mkdoit2 -o labdoit  lab.doit && chmod a+x labdoit
serdoit : ser.doit
	mkdoit2 -o serdoit  ser.doit && chmod a+x serdoit
playdoit : play.doit
	mkdoit2 -o playdoit  play.doit && chmod a+x playdoit
uavdisp : uavdisp.o integrate.o uavdispoui.o
	$(LINK.norm) uavdisp.o integrate.o uavdispoui.o
	$(OUIUSE) uavdispoui.c
uavalgo : uavalgo.o integrate.o reveal.o nasdat.o kusend.o commands.o uavalgooui.o
	$(LINK.norm) uavalgo.o integrate.o reveal.o nasdat.o kusend.o commands.o uavalgooui.o
	$(OUIUSE) uavalgooui.c
labalgo : labalgo.o integrate.o reveal.o nasdat.o kusend.o commands.o labalgooui.o
	$(LINK.norm) labalgo.o integrate.o reveal.o nasdat.o kusend.o commands.o labalgooui.o
	$(OUIUSE) labalgooui.c
calalgo : calalgo.o valves.o calalgooui.o
	$(LINK.norm) calalgo.o valves.o calalgooui.o
	$(OUIUSE) calalgooui.c
uav.sft : uavslp.sol uav.sol
	$(SOLFMT)  uavslp.sol uav.sol
eng1ext : eng1ext.o eng1extoui.o
	$(LINK.norm) eng1ext.o eng1extoui.o
	$(OUIUSE) eng1extoui.c
eng2ext : eng2ext.o eng2extoui.o
	$(LINK.norm) eng2ext.o eng2extoui.o
	$(OUIUSE) eng2extoui.c
o3ext : o3ext.o o3extoui.o
	$(LINK.norm) o3ext.o o3extoui.o
	$(OUIUSE) o3extoui.c
o3xext : o3xext.o o3xextoui.o
	$(LINK.norm) o3xext.o o3xextoui.o
	$(OUIUSE) o3xextoui.c
h2oext : h2oext.o h2oextoui.o
	$(LINK.norm) h2oext.o h2oextoui.o
	$(OUIUSE) h2oextoui.c
gcitxext : gcitxext.o gcitx.o gcitxextoui.o
	$(LINK.norm) gcitxext.o gcitx.o gcitxextoui.o
	$(OUIUSE) gcitxextoui.c
intext : intext.o integrate.o intextoui.o
	$(LINK.norm) intext.o integrate.o intextoui.o
	$(OUIUSE) intextoui.c
uavclt : valves.o commands.o uavclt.o uavcltoui.o
	$(LINK.norm) valves.o commands.o uavclt.o uavcltoui.o
	$(OUIUSE) uavcltoui.c
uavsrvr : valves.o commands.o uavsrvr.o uavsrvroui.o
	$(LINK.priv) valves.o commands.o uavsrvr.o uavsrvroui.o
	$(OUIUSE) uavsrvroui.c
	promote uavsrvr
uavcol.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc basecol.tmc
	$(TMC.col) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc basecol.tmc
uavcoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
uavcol.o : uavcol.c
uavcoloui.o : uavcoloui.c
main.fld : main.tbl
	$(TABLE) main.tbl
h2o.fld : h2o.tbl
	$(TABLE) h2o.tbl
uavdisp.tmc : main.fld h2o.fld
	$(FLD2DISP) main.fld h2o.fld
uavdisptmg.tmc : plot.tmg
	$(TMG2TMC) plot.tmg
uavdisp.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc bittxt.tmc uavdisptmg.tmc uavdisp.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc bittxt.tmc uavdisptmg.tmc uavdisp.tmc
uavdispoui.c : $(OUIDIR)/nl_cons.oui $(OUIDIR)/tmg.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nl_cons.oui $(OUIDIR)/tmg.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
uavdisp.o : uavdisp.c
integrate.o : integrate.c
uavdispoui.o : uavdispoui.c
uavalgoa.tmc : uav.tma uavsrvr
	$(SERVER) uavsrvr
	$(TMCALGO) uav.tma
uavalgo.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc uavalgoa.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc uavalgoa.tmc
uavalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
uavalgo.o : uavalgo.c
reveal.o : reveal.c
nasdat.o : nasdat.c
kusend.o : kusend.c
commands.o : commands.c
uavalgooui.o : uavalgooui.c
labalgoa.tmc : lab.tma uavsrvr
	$(SERVER) uavsrvr
	$(TMCALGO) lab.tma
labalgo.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc labalgoa.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intdsp.tmc labalgoa.tmc
labalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
labalgo.o : labalgo.c
labalgooui.o : labalgooui.c
calalgoa.tmc : cal.tma uavsrvr
	$(SERVER) uavsrvr
	$(TMCALGO) cal.tma
calalgo.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc calalgoa.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc calalgoa.tmc
calalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
calalgo.o : calalgo.c
valves.o : valves.c
calalgooui.o : calalgooui.c
uavslp.sol : uav.slp
	$(SLP2SOL) uav.slp
eng1extedf.oui : eng1.edf
	$(EDF2OUI) eng1.edf
eng1ext.tmc : eng1.edf
	$(EDF2EXT) eng1.edf
eng1ext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc eng1ext.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc eng1ext.tmc
eng1extoui.c : eng1extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) eng1extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
eng1ext.o : eng1ext.c
eng1extoui.o : eng1extoui.c
eng2extedf.oui : eng2.edf
	$(EDF2OUI) eng2.edf
eng2ext.tmc : eng2.edf
	$(EDF2EXT) eng2.edf
eng2ext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc eng2ext.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc eng2ext.tmc
eng2extoui.c : eng2extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) eng2extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
eng2ext.o : eng2ext.c
eng2extoui.o : eng2extoui.c
o3extedf.oui : o3data.edf
	$(EDF2OUI) o3data.edf
o3dataext.tmc : o3data.edf
	$(EDF2EXT) o3data.edf
o3ext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc o3dataext.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc o3dataext.tmc
o3extoui.c : o3extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) o3extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
o3ext.o : o3ext.c
o3extoui.o : o3extoui.c
o3xextedf.oui : o3xdata.edf
	$(EDF2OUI) o3xdata.edf
o3xdataext.tmc : o3xdata.edf
	$(EDF2EXT) o3xdata.edf
o3xext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc o3xdataext.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc o3xdataext.tmc
o3xextoui.c : o3xextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) o3xextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
o3xext.o : o3xext.c
o3xextoui.o : o3xextoui.c
h2oextedf.oui : h2odata.edf
	$(EDF2OUI) h2odata.edf
h2odataext.tmc : h2odata.edf
	$(EDF2EXT) h2odata.edf
h2oext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc h2odataext.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc h2odataext.tmc
h2oextoui.c : h2oextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) h2oextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
h2oext.o : h2oext.c
h2oextoui.o : h2oextoui.c
gcitxext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc gcitx.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc gcitx.tmc
gcitxextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
gcitxext.o : gcitxext.c
gcitx.o : gcitx.c
gcitxextoui.o : gcitxextoui.c
intext.c : base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intres.tmc
	$(TMC) base.tmc adr2000.tmc gc.tmc analog.tmc omega.tmc digital.tmc valco.tmc ozone.tmc maycomm.tmc vaisala.tmc int.tmc intres.tmc
intextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
intext.o : intext.c
intextoui.o : intextoui.c
uavslp.cmd : uav.slp
	$(SLP2CMD) uav.slp
uavcmd.c : uav.cmd uavslp.cmd
	$(CMDGEN) -d uavcmd.dat uav.cmd uavslp.cmd
uavclt.o : uavcmd.c
	$(COMPILE.clt) uavcmd.c
uavcltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
uavcltoui.o : uavcltoui.c
uavsrvr.o : uavcmd.c
	$(COMPILE.srvr) uavcmd.c
uavsrvroui.c : $(OUIDIR)/server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/server.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
uavsrvroui.o : uavsrvroui.c
MODEL=l
CPU=-2
OPTIM=-N8k
uavdoit : main.fld h2o.fld normal.cfg
dc8doit : main.fld h2o.fld normal.cfg
caldoit : main.fld h2o.fld normal.cfg
labdoit : main.fld h2o.fld normal.cfg
playdoit : main.fld h2o.fld normal.cfg
serdoit : main.fld h2o.fld normal.cfg
addresses.h : uavcol.c
addresses.h : uavcmd.c
uavsrvr.o : addresses.h
uavcol : addresses.h 
