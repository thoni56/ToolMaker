# Makefile for lmk
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

INCLUDE	= -I../tmk -I../imp

LDLIBS = ../tmk/libtmk.a ../imp/imp.a

VERSIONOBJECTS = \
	lmkPaSema.o lmkParse.o \
	lmkErr.o \
	lmkScan.o \
	lmkScSema.o \
	lmkList.o \
	lmkTab.o \
	lmk.o

OBJECTS = $(VERSIONOBJECTS) version.o

#
all debug: lmkobj
	install -C -b List.imp ../../lib/ansi-c/

test:
	cd testing; make

install: installdirs
	install -C List.imp $(DESTLIB)/lib/ansi-c
	install lmk $(DESTROOT)/bin

# To regenerate from tmk sources, do:
tm: tmk lmkobj

#-- Utility targets below

tmk:
	pmk lmk
	smk lmk
	lmk lmk

lmkobj : checkARCH $(TMARCH) | ../../bin
	install lmk ../../bin/

$(TMARCH): $(OBJECTS) $(LDLIBS)
	$(CC) -o lmk $(CFLAGS) $(OBJECTS) $(LDLIBS) $(LDFLAGS)

#--
include ../common.mk
-include *.d
