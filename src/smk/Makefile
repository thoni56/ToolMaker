# Makefile for ScannerMaker
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

INCLUDE	= -I../tmk -I../imp

LIBS    = ../tmk/libtmk.a ../imp/imp.a

VERSIONOBJECTS	= smkPaSema.o smkScSema.o smkParse.o smkErr.o smkScan.o smkList.o smk.o token.o \
	scanner.o vocabulary.o definition.o rule.o ast.o lmprintf.o name.o char.o nfa.o \
	lookahead.o dfa.o map.o pack.o write.o time.o \
	action.o set.o screen.o smalloc.o nfas.o common.o

OBJECTS = $(VERSIONOBJECTS) version.o

################################################################################
#
#
all debug : smkobj
	install -C -b Scan.imp ../../lib/ansi-c

################################################################################
#
#
# Install in DESTROOT/bin, DESTROOT/lib/ToolMaker=DESTLIB & DESTROOT/man
install: installdirs
	install -C Scan.imp $(DESTLIB)/lib/ansi-c
	install smk $(DESTROOT)/bin

smkobj: checkARCH $(TMARCH)
	install smk ../../bin/

$(TMARCH): $(OBJECTS) $(LIBS)
	$(CC) -o smk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS) $(MALLOCDEBUG)

# To regenerate from tmk sources, do:
tm: tmk smkobj

tmk:
	../../bin/pmk smk
	../../bin/smk smk
	../../bin/lmk smk

test:
	cd testing; make

#--
include ../common.mk
-include *.d
