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

test: unit
	cd testing; make

# Unit tests, in Cgreen. Built with the address sanitizer on purpose: a
# formatting bug that overruns its buffer can still return the string the
# test asked for, so without it a broken tistr() would pass.
#
# Cgreen is an extra dependency, so skip rather than fail if it is absent.
# Do not add -I. here, or Cgreen's <time.h> resolves to smk's own.
UNITTESTS = time_tests

.PHONY: unit
unit:
	@if echo '#include <cgreen/cgreen.h>' | $(CC) -fsyntax-only -xc - 2>/dev/null; then \
		for t in $(UNITTESTS); do \
			$(CC) -Wall -ggdb -fsanitize=address -o $$t $$t.c $${t%_tests}.c -lcgreen || exit 1; \
			ASAN_OPTIONS=detect_leaks=0 ./$$t || exit 1; \
		done; \
	else \
		echo "Cgreen not found, skipping unit tests (see https://github.com/cgreen-devs/cgreen)"; \
	fi

# Adds a prerequisite to the clean rule in common.mk without redefining it.
clean: clean-unit

.PHONY: clean-unit
clean-unit:
	rm -f $(UNITTESTS)

#--
include ../common.mk
-include *.d
