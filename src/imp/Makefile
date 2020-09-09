# Makefile for imp
#
# This makefile is to compile directly from existing sources
#

include ../defines.mk

LIB = imp.a

#--

VERSIONOBJECTS= impParse.o impPaSema.o impErr.o impList.o impScan.o impScSema.o \
	ast.o name.o impMacro.o timing.o

OBJECTS	= $(VERSIONOBJECTS) version.o

all debug trace : impobj

install:
	install imp $(DESTROOT)/bin

test:
	cd testing; make

tm: tmk impobj


#-- Utility targets below

tmk:
	../../bin/smk imp
	../../bin/pmk imp
	../../bin/lmk imp

.PHONY: $(impobj)
impobj:	checkARCH $(TMARCH)
	mkdir -p ../../bin && cp imp.exe ../../bin/

.PHONY: $(TMARCH)
$(TMARCH): $(LIB) imp.o
	$(CC) -o imp $(CFLAGS) imp.o $(LIB) $(LDFLAGS)

$(LIB): $(OBJECTS)
	ar rv $(LIB) $(OBJECTS)
	-ranlib $(LIB)

impParse.o: impParse.c
impPaSema.o: impPaSema.c
impScan.o: impScan.c
impScSema.o: impScSema.c
impList.o: impList.c

#-

clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt imp imp.a

depend file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJECTS:.o=.c) ; do /lib/cpp $(INCLUDE) -M $$file | egrep -v '/usr/include|\.c$$' | cat >> Makefile ; echo -n . ; done
	@echo "done."

include ../common.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
impParse.o: ./ast.h
$(LIB)(impParse.o): ./ast.h
impParse.o: ./impCommon.h
$(LIB)(impParse.o): ./impCommon.h
impParse.o: ./impMacro.h
$(LIB)(impParse.o): ./impMacro.h
impParse.o: ./impScan.h
$(LIB)(impParse.o): ./impScan.h
impParse.o: ./impCommon.h
$(LIB)(impParse.o): ./impCommon.h
impParse.o: ./impList.h
$(LIB)(impParse.o): ./impList.h
impParse.o: ./impCommon.h
$(LIB)(impParse.o): ./impCommon.h
impParse.o: ./impCommon.h
$(LIB)(impParse.o): ./impCommon.h
impPaSema.o: ./ast.h
$(LIB)(impPaSema.o): ./ast.h
impPaSema.o: ./impCommon.h
$(LIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impMacro.h
$(LIB)(impPaSema.o): ./impMacro.h
impPaSema.o: ./impScan.h
$(LIB)(impPaSema.o): ./impScan.h
impPaSema.o: ./impCommon.h
$(LIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impList.h
$(LIB)(impPaSema.o): ./impList.h
impPaSema.o: ./impCommon.h
$(LIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impParse.h
$(LIB)(impPaSema.o): ./impParse.h
impPaSema.o: ./ast.h
$(LIB)(impPaSema.o): ./ast.h
impPaSema.o: ./impCommon.h
$(LIB)(impPaSema.o): ./impCommon.h
impErr.o: ./ast.h
$(LIB)(impErr.o): ./ast.h
impErr.o: ./impCommon.h
$(LIB)(impErr.o): ./impCommon.h
impErr.o: ./impMacro.h
$(LIB)(impErr.o): ./impMacro.h
impErr.o: ./impScan.h
$(LIB)(impErr.o): ./impScan.h
impErr.o: ./impCommon.h
$(LIB)(impErr.o): ./impCommon.h
impErr.o: ./impList.h
$(LIB)(impErr.o): ./impList.h
impErr.o: ./impCommon.h
$(LIB)(impErr.o): ./impCommon.h
impErr.o: ./impErr.h
$(LIB)(impErr.o): ./impErr.h
impErr.o: ./impList.h
$(LIB)(impErr.o): ./impList.h
impErr.o: ./impCommon.h
$(LIB)(impErr.o): ./impCommon.h
impList.o: ./impList.h
$(LIB)(impList.o): ./impList.h
impList.o: ./impCommon.h
$(LIB)(impList.o): ./impCommon.h
impScan.o: ./impScan.h
$(LIB)(impScan.o): ./impScan.h
impScan.o: ./impCommon.h
$(LIB)(impScan.o): ./impCommon.h
impScPaSema.o: ./impScan.h
$(LIB)(impScPaSema.o): ./impScan.h
impScPaSema.o: ./impCommon.h
$(LIB)(impScPaSema.o): ./impCommon.h
impScPaSema.o: ./impMacro.h
$(LIB)(impScPaSema.o): ./impMacro.h
impScPaSema.o: ./impList.h
$(LIB)(impScPaSema.o): ./impList.h
impScPaSema.o: ./impCommon.h
$(LIB)(impScPaSema.o): ./impCommon.h
version.o: ./version.h
$(LIB)(version.o): ./version.h
ast.o: ./impList.h
$(LIB)(ast.o): ./impList.h
ast.o: ./impCommon.h
$(LIB)(ast.o): ./impCommon.h
ast.o: ./impMacro.h
$(LIB)(ast.o): ./impMacro.h
ast.o: ./name.h
$(LIB)(ast.o): ./name.h
ast.o: ./ast.h
$(LIB)(ast.o): ./ast.h
ast.o: ./impCommon.h
$(LIB)(ast.o): ./impCommon.h
ast.o: ./impMacro.h
$(LIB)(ast.o): ./impMacro.h
ast.o: ./ast.h
$(LIB)(ast.o): ./ast.h
name.o: ./name.h
$(LIB)(name.o): ./name.h
name.o: ./ast.h
$(LIB)(name.o): ./ast.h
name.o: ./impCommon.h
$(LIB)(name.o): ./impCommon.h
name.o: ./impMacro.h
$(LIB)(name.o): ./impMacro.h
name.o: ./ast.h
$(LIB)(name.o): ./ast.h
name.o: ./impScan.h
$(LIB)(name.o): ./impScan.h
name.o: ./impCommon.h
$(LIB)(name.o): ./impCommon.h
name.o: ./impList.h
$(LIB)(name.o): ./impList.h
name.o: ./impCommon.h
$(LIB)(name.o): ./impCommon.h
impMacro.o: ./impMacro.h
$(LIB)(impMacro.o): ./impMacro.h
impMacro.o: ./impList.h
$(LIB)(impMacro.o): ./impList.h
impMacro.o: ./impCommon.h
$(LIB)(impMacro.o): ./impCommon.h
impMacro.o: ./impScan.h
$(LIB)(impMacro.o): ./impScan.h
impMacro.o: ./impCommon.h
$(LIB)(impMacro.o): ./impCommon.h
impMacro.o: ./ast.h
$(LIB)(impMacro.o): ./ast.h
impMacro.o: ./impCommon.h
$(LIB)(impMacro.o): ./impCommon.h
impMacro.o: ./impMacro.h
$(LIB)(impMacro.o): ./impMacro.h
impMacro.o: ./timing.h
$(LIB)(impMacro.o): ./timing.h
impMacro.o: ./version.h
$(LIB)(impMacro.o): ./version.h
timing.o: ./timing.h
$(LIB)(timing.o): ./timing.h
