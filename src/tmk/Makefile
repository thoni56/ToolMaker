# Makefile for tmk
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

LIB     = libtmk.a

OBJECTS = tmkPaSema.o tmkParse.o tmkErr.o tmkScan.o tmkScSema.o tmkOpts.o tmkCommon.o

#--
all debug: $(TMARCH)

# Install in DESTROOT/bin, DESTROOT/lib/ToolMaker=DESTLIB & DESTROOT/man
install: installdirs
	install -C Common.imp $(DESTLIB)/lib/ansi-c

tm: tmk $(TMARCH)

test:

#-- Utility targets below

# To regenerate from tmk sources, do:
.PHONY: tmk
tmk:
	../../bin/smk tmk
	../../bin/pmk tmk
	../../bin/lmk tmk

.PHONY: $(TMARCH)
$(TMARCH): tmkobj

tmkobj: checkARCH $(LIB) version.c

.PRECIOUS: $(LIB)
$(LIB): $(OBJECTS)
	ar r $(LIB) $?
	-ranlib $(LIB)
	install -C -b Common.imp ../../lib/ansi-c

print:
	@echo TMARCH=$(TMARCH)
	@echo OBJECTS=$(OBJECTS)
	@echo LIB=$(LIB)

#--
clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt $(LIB)

include ../common.mk
-include *.d
