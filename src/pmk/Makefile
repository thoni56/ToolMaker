# Makefile for ParserMaker
#
# This makefile is to compile directly from create sources
# without license...
#

TMARCH	= cygwin
mingw:	TMARCH	= mingw
mingw:	MINGW	= -mno-cygwin
mingw: CQ = -DMINGW
cygwin: CQ = -DCYGWIN

DEBUG	= -g

INCLUDE	= -I../tmk -I../imp

CFLAGS	= $(CQ) $(DEBUG) $(INCLUDE) $(MINGW)

LDFLAGS	= -lm $(LQ)

CC	= $(GCC)
CPP	= $(GCC)
GCC	= gcc -Wall

VERSIONOBJECTS = \
	pack.o \
	pmkErr.o \
	pmkList.o \
	pmkParse.o \
	pmkScan.o \
	pmkPaSema.o \
	pmkScSema.o \
	pmkSymTab.o \
	pmkTab.o \
	pwDbg.o \
	pwGe.o \
	pwLog.o \
	pwPack.o \
	pwSymSet.o \
	pwsGrm.o \
	pwsOrd.o \
	pwsQueue.o \
	pwsWrit.o \
	set.o \
	timing.o \
	pmk.o


OBJECTS = $(VERSIONOBJECTS) version.o

LIBS	= \
	../tmk/libtmk.a \
	../imp/imp.a


#--

all debug: pmkobj
	install -C -b Parse.imp Err.imp ../../lib/ansi-c

install: installdirs
	install -C Parse.imp Err.imp $(DESTLIB)/lib/ansi-c
	install pmk $(DESTROOT)/bin

tm: tmk pmkobj


#-- Utility targets below

tmk:
	../../bin/pmk pmk
	../../bin/smk pmk
	../../bin/lmk pmk

pmkobj: checkARCH $(TMARCH)
	install pmk ../../bin/

mingw cygwin sun3 sun4 solaris1 solaris2: ../license/license.h ../imp/impMacro.h ../tmk/tmk.h ../tmk/tmkCommon.h $(OBJECTS) $(LIBS)
	$(CC) -o pmk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS)

pmkParse.o: pmkParse.c
pmkPaSema.o: pmkPaSema.c
pmkErr.o: pmkErr.c
pmkScan.o: pmkScan.c
pmkScSema.o: pmkScSema.c
pmkList.o: pmkList.c

test:
	cd testing; make

#--
clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt pmk

veryclean: clean
	rm pmk.voc pmkParse.* pmkScan.* pmkScSema.* pmkPaSema.* pmkCommon.h pmkList.* pmkErr.*

FILETER = | sed -e "\,/usr/include, d" | sort -u | grep -v

depend file:
	@echo -n "Make depend "
	@-rm dependencies.mk
	@for file in $(OBJECTS:.o=.c) ; do $(CPP) $(INCLUDE) -MM $$file | cat >> dependencies.mk ; echo -n . ; done
	@echo "done."

include ../common.mk
include dependencies.mk
