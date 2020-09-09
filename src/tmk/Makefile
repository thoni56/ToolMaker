# Makefile for tmk
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

LIB = libtmk.a
OBJECTS = tmkPaSema.o tmkParse.o tmkErr.o tmkScan.o tmkScSema.o tmkOpts.o tmkCommon.o

#--
all debug: $(TMARCH)

# Install in DESTROOT/bin, DESTROOT/lib/ToolMaker=DESTLIB & DESTROOT/man
install: installdirs
	install -C Common.imp $(DESTLIB)/lib/ansi-c

# To regenerate from tmk sources, do:
tm: tmk $(TMARCH)

test:

#-- Utility targets below

.PHONY: tmk
tmk:
	smk tmk
	pmk tmk
	lmk tmk

.PHONY: $(TMARCH)
$(TMARCH): tmkobj

tmkobj: checkARCH $(LIB) version.c

.PRECIOUS: $(LIB)
$(LIB): $(OBJECTS)
	ar r $(LIB) $?
	-ranlib $(LIB)
	install -C -b Common.imp ../../lib/ansi-c

#-
include ../common.mk
-include *.d
