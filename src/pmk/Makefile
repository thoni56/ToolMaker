# Makefile for ParserMaker
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

INCLUDE	= -I../tmk -I../imp

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

LIBS = ../tmk/libtmk.a ../imp/imp.a

#--

all debug: pmkobj
	install -C -b Parse.imp Err.imp ../../lib/ansi-c

install: installdirs
	install -C Parse.imp Err.imp $(DESTLIB)/lib/ansi-c
	install pmk $(DESTROOT)/bin

# To regenerate from tmk sources, do:
tm: tmk pmkobj

#-- Utility targets below

tmk:
	pmk pmk
	smk pmk
	lmk pmk

pmkobj: checkARCH $(TMARCH) | ../../bin
	install pmk ../../bin/

$(TMARCH): $(OBJECTS) $(LIBS)
	$(CC) -o pmk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS)

test:
	cd testing; make

#--
include ../common.mk
-include *.d
