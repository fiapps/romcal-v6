#ymake
#--------------------------------------------------------------------
#
#	@(#)ROMCAL Makefile 6.5 03/01/06 16:25:30
#
#	Copyright (C) 1993,1995, Kenneth G. Bath
#	Permission to use and modify this software and its
#	documentation for any purpose other than its incorporation
#	into a commercial product is hereby granted without fee.
#
#	Permission to copy and distribute this software and its
#	documentation only for non-commercial use is also granted
#	without fee, provided, however, that the above copyright
#	notice appear in all copies, that both that copyright
#	notice and this permission notice appear in supporting
#	documentation. The author makes no representations about
#	the suitability of this software for any purpose. It is
#	provided "as is" without express or implied warranty.
#
#----------------------- Makefile History ---------------------------
#
#	08feb02 : Updated for Version 5, kgb
#	09Dec02 :    printtxt.c	kbath
#	09Dec02 :    printcal.c	kbath
#	09Dec02 :    printhtm.c	kbath
#	09Dec02 :    printics.c	kbath
#	09Dec02 :    printmon.c	kbath
#	09Dec02 :    printpsc.c	kbath
#	09Dec02 :    printpsg.c	kbath
#	09Dec02 :    printrtf.c	kbath
#	09Dec02 :    printtxt.c	kbath
#	09Dec02 :    printweb.c	kbath
#	09Dec02 :    mkfix.c	kbath
#	09Dec02 :    mkhead.c	kbath
#	09Dec02 :    romcal.c	kbath
#	09Dec02 :    proper.c	kbath
#	09Dec02 :    parse.c	kbath
#	09Dec02 :    xmas1.c	kbath
#	09Dec02 :    xmas2.c	kbath
#	09Dec02 :    doy.c	kbath
#	09Dec02 :    caltail.c	kbath
#	09Dec02 :    advent.c	kbath
#	09Dec02 :    gencel.c	kbath
#	09Dec02 :    datestr.c	kbath
#	09Dec02 :    calhead.c	kbath
#	09Dec02 :    eastdate.c	kbath
#	09Dec02 :    leapyear.c	kbath
#	09Dec02 :    easter.c	kbath
#	09Dec02 :    ord1.c	kbath
#	09Dec02 :    ord2.c	kbath
#	09Dec02 :    center.c	kbath
#	09Dec02 :    lent.c	kbath
#	09Dec02 :    init.c	kbath
#	09Dec02 :    monhead.c	kbath
#	09Dec02 :    psformat.c	kbath
#	09Dec02 :    splitstr.c	kbath
#	09Dec02 :    montail.c	kbath
#	09Dec02 :    rtfrow.c	kbath
#	09Dec02 :    doydate.c	kbath
#	09Dec02 :    version.c	kbath
#	09Dec02 :    printcal.c	kbath
#	09Dec02 :    printhtm.c	kbath
#	09Dec02 :    printics.c	kbath
#	09Dec02 :    printmon.c	kbath
#	09Dec02 :    printpsc.c	kbath
#	09Dec02 :    printpsg.c	kbath
#	09Dec02 :    printrtf.c	kbath
#	09Dec02 :    printtxt.c	kbath
#	09Dec02 :    printweb.c	kbath
#>
#--------------------------------------------------------------------
OBJECTS=\
printweb.o\
printtxt.o\
printrtf.o\
printpsg.o\
printpsc.o\
printmon.o\
printics.o\
printhtm.o\
printcal.o\
version.o\
doydate.o\
rtfrow.o\
montail.o\
splitstr.o\
psformat.o\
monhead.o\
init.o\
lent.o\
center.o\
ord2.o\
ord1.o\
easter.o\
leapyear.o\
eastdate.o\
calhead.o\
datestr.o\
gencel.o\
advent.o\
caltail.o\
doy.o\
xmas2.o\
xmas1.o\
parse.o\
proper.o\
romcal.o\
Makefile

CC=cc
CFLAGS=
#
# Files with a .hdr extension are used as templates for the different 
# output formats (PostScript, HTML, etc.). These are converted into
# header files for use by the C Language code. The following is a 
# Makefile rule which associates the .hdr files with the .h files they 
# control. 
#
%.h: %.hdr
	cat $< | ./mkhead | \
	   sed 's/__MKHEAD__/$*/' | \
	   sed 's/__YEAR__/%d/' | \
	   sed 's/__MONTH__/%s/' > $@

all: romcal eastdate

clean:
	$(RM) *.o  fixed.h calhead?.h caltail?.h monhead?.h montail?.h romcal mkfix mkhead eastdate

fixed.h: mkfix fixed.dat
	./mkfix

calheadH.h: mkhead calheadH.hdr
calheadR.h: mkhead calheadR.hdr
calheadG.h: mkhead calheadG.hdr
calheadC.h: mkhead calheadC.hdr
monheadH.h: mkhead monheadH.hdr
monheadR.h: mkhead monheadR.hdr
caltailH.h: mkhead caltailH.hdr
caltailR.h: mkhead caltailR.hdr

romcal: $(OBJECTS)
	$(CC) $(CFLAGS) -o romcal $(OBJECTS:Makefile=)

mkfix: mkfix.o 
	$(CC) $(CFLAGS) -o mkfix mkfix.o

mkhead: mkhead.o 
	$(CC) $(CFLAGS) -o mkhead mkhead.o

eastdate: eastdate.c
	$(CC) -DMAINPROG eastdate.c -o eastdate

eastedae.o: proto.h
mkfix.o: romcal.h
mkfix.o: proto.h
mkfix.o: mkfix.c
mkfix.o: caltypes.h
mkhead.o: mkhead.c
romcal.o: romcal.h
romcal.o: romcal.c
romcal.o: proto.h
romcal.o: caltypes.h
proper.o: romcal.h
proper.o: proto.h
proper.o: proper.c
proper.o: fixed.h
proper.o: caltypes.h
parse.o: romcal.h
parse.o: proto.h
parse.o: parse.c
parse.o: caltypes.h
xmas1.o: xmas1.c
xmas1.o: romcal.h
xmas1.o: proto.h
xmas1.o: caltypes.h
xmas2.o: xmas2.c
xmas2.o: romcal.h
xmas2.o: proto.h
xmas2.o: caltypes.h
doy.o: doy.c
caltail.o: romcal.h
caltail.o: proto.h
caltail.o: caltypes.h
caltail.o: caltailR.h
caltail.o: caltailH.h
caltail.o: caltail.c
advent.o: romcal.h
advent.o: proto.h
advent.o: caltypes.h
advent.o: advent.c
gencel.o: romcal.h
gencel.o: proto.h
gencel.o: gencel.c
gencel.o: caltypes.h
datestr.o: datestr.c
calhead.o: romcal.h
calhead.o: proto.h
calhead.o: caltypes.h
calhead.o: calheadR.h
calhead.o: calheadH.h
calhead.o: calheadG.h
calhead.o: calheadC.h
calhead.o: calhead.c
eastdate.o: romcal.h
eastdate.o: proto.h
eastdate.o: eastdate.c
eastdate.o: caltypes.h
leapyear.o: romcal.h
leapyear.o: proto.h
leapyear.o: leapyear.c
leapyear.o: caltypes.h
easter.o: romcal.h
easter.o: proto.h
easter.o: easter.c
easter.o: caltypes.h
ord1.o: romcal.h
ord1.o: proto.h
ord1.o: ord1.c
ord1.o: caltypes.h
ord2.o: romcal.h
ord2.o: proto.h
ord2.o: ord2.c
ord2.o: caltypes.h
center.o: romcal.h
center.o: proto.h
center.o: center.c
center.o: caltypes.h
lent.o: romcal.h
lent.o: proto.h
lent.o: lent.c
lent.o: caltypes.h
init.o: romcal.h
init.o: proto.h
init.o: init.c
init.o: caltypes.h
monhead.o: romcal.h
monhead.o: proto.h
monhead.o: montab.h
monhead.o: monheadR.h
monhead.o: monheadH.h
monhead.o: monhead.c
monhead.o: caltypes.h
psformat.o: psformat.c
psformat.o: montab.h
psformat.o: caltypes.h
splitstr.o: splitstr.c
montail.o: romcal.h
montail.o: proto.h
montail.o: montail.c
montail.o: caltypes.h
rtfrow.o: rtfrow.c
rtfrow.o: caltypes.h
doydate.o: doydate.c
version.o: version.c
printcal.o: romcal.h
printcal.o: proto.h
printcal.o: printcal.c
printcal.o: caltypes.h
printhtm.o: romcal.h
printhtm.o: proto.h
printhtm.o: printstr.h
printhtm.o: printhtm.c
printhtm.o: montab.h
printhtm.o: caltypes.h
printics.o: romcal.h
printics.o: proto.h
printics.o: printstr.h
printics.o: printics.c
printics.o: montab.h
printics.o: caltypes.h
printmon.o: romcal.h
printmon.o: proto.h
printmon.o: printstr.h
printmon.o: printmon.c
printmon.o: montab.h
printmon.o: caltypes.h
printpsc.o: romcal.h
printpsc.o: proto.h
printpsc.o: printstr.h
printpsc.o: printpsc.c
printpsc.o: montab.h
printpsc.o: caltypes.h
printpsg.o: romcal.h
printpsg.o: proto.h
printpsg.o: printstr.h
printpsg.o: printpsg.c
printpsg.o: montab.h
printpsg.o: caltypes.h
printrtf.o: romcal.h
printrtf.o: proto.h
printrtf.o: printstr.h
printrtf.o: printrtf.c
printrtf.o: montab.h
printrtf.o: caltypes.h
printtxt.o: romcal.h
printtxt.o: proto.h
printtxt.o: printtxt.c
printtxt.o: printstr.h
printtxt.o: montab.h
printtxt.o: caltypes.h
printweb.o: romcal.h
printweb.o: proto.h
printweb.o: printweb.c
printweb.o: printstr.h
printweb.o: caltypes.h
