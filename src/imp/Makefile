# Makefile for imp
#
# To build from current sources do: make
# To re-generate sources from ToolMaker sources: make tm

include ../defines.mk

LIB = imp.a

#--

VERSIONOBJECTS= impParse.o impPaSema.o impErr.o impList.o impScan.o impScSema.o \
	ast.o name.o impMacro.o timing.o

OBJECTS	= $(VERSIONOBJECTS) version.o

debug: CFLAGS += -DDEBUG
all debug trace : impobj

install:
	install imp $(DESTROOT)/bin

test:
	cd testing; make

# To regenerate from tmk sources, do:
tm: tmk impobj

#-- Utility targets below

tmk:
	smk imp
	pmk imp
	lmk imp

.PHONY: $(impobj)
impobj:	checkARCH $(TMARCH) | ../../bin
	install imp ../../bin/

.PHONY: $(TMARCH)
$(TMARCH): $(LIB) imp.o
	$(CC) -o imp $(CFLAGS) imp.o $(LIB) $(LDFLAGS)

$(LIB): $(OBJECTS)
	ar rv $(LIB) $(OBJECTS)
	-ranlib $(LIB)

#-
include ../common.mk
-include *.d
