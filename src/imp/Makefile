# Makefile for imp
#
# This makefile is to compile directly from existing sources
#

TMARCH	= cygwin
mingw:	TMARCH	= mingw
mingw:	MINGW	= -mno-cygwin -DMINGW

CC	= $(GCC) -Wall
#CQ	= -DWIN32

CFLAGS	= -g $(CQ) $(INCLUDE) $(MINGW)

GCC	= gcc

IMPLIB = imp.a


#--

VERSIONOBJECTS= impParse.o impPaSema.o impErr.o impList.o impScan.o impScSema.o \
	ast.o name.o impMacro.o timing.o

OBJECTS	= $(VERSIONOBJECTS) version.o

all debug trace : impobj

impobj:	checkARCH $(TMARCH)
	cp imp.exe ../../bin/

mingw cygwin sun3 sun4 solaris1: $(IMPLIB) imp.o
	$(CC) -o imp $(CFLAGS) imp.o $(IMPLIB) $(LDFLAGS)

solaris2: $(IMPLIB) imp.o
	$(CC) -o imp $(CFLAGS) imp.o $(IMPLIB) $(LDFLAGS)


$(IMPLIB): $(OBJECTS)
	ar rv $(IMPLIB) $(OBJECTS)
	-ranlib $(IMPLIB)

impParse.o: impParse.c
impPaSema.o: impPaSema.c
impScan.o: impScan.c
impScSema.o: impScSema.c
impList.o: impList.c

#-

test:
	cd TEST; jregr

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
$(IMPLIB)(impParse.o): ./ast.h
impParse.o: ./impCommon.h
$(IMPLIB)(impParse.o): ./impCommon.h
impParse.o: ./impMacro.h
$(IMPLIB)(impParse.o): ./impMacro.h
impParse.o: ./impScan.h
$(IMPLIB)(impParse.o): ./impScan.h
impParse.o: ./impCommon.h
$(IMPLIB)(impParse.o): ./impCommon.h
impParse.o: ./impList.h
$(IMPLIB)(impParse.o): ./impList.h
impParse.o: ./impCommon.h
$(IMPLIB)(impParse.o): ./impCommon.h
impParse.o: ./impCommon.h
$(IMPLIB)(impParse.o): ./impCommon.h
impPaSema.o: ./ast.h
$(IMPLIB)(impPaSema.o): ./ast.h
impPaSema.o: ./impCommon.h
$(IMPLIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impMacro.h
$(IMPLIB)(impPaSema.o): ./impMacro.h
impPaSema.o: ./impScan.h
$(IMPLIB)(impPaSema.o): ./impScan.h
impPaSema.o: ./impCommon.h
$(IMPLIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impList.h
$(IMPLIB)(impPaSema.o): ./impList.h
impPaSema.o: ./impCommon.h
$(IMPLIB)(impPaSema.o): ./impCommon.h
impPaSema.o: ./impParse.h
$(IMPLIB)(impPaSema.o): ./impParse.h
impPaSema.o: ./ast.h
$(IMPLIB)(impPaSema.o): ./ast.h
impPaSema.o: ./impCommon.h
$(IMPLIB)(impPaSema.o): ./impCommon.h
impErr.o: ./ast.h
$(IMPLIB)(impErr.o): ./ast.h
impErr.o: ./impCommon.h
$(IMPLIB)(impErr.o): ./impCommon.h
impErr.o: ./impMacro.h
$(IMPLIB)(impErr.o): ./impMacro.h
impErr.o: ./impScan.h
$(IMPLIB)(impErr.o): ./impScan.h
impErr.o: ./impCommon.h
$(IMPLIB)(impErr.o): ./impCommon.h
impErr.o: ./impList.h
$(IMPLIB)(impErr.o): ./impList.h
impErr.o: ./impCommon.h
$(IMPLIB)(impErr.o): ./impCommon.h
impErr.o: ./impErr.h
$(IMPLIB)(impErr.o): ./impErr.h
impErr.o: ./impList.h
$(IMPLIB)(impErr.o): ./impList.h
impErr.o: ./impCommon.h
$(IMPLIB)(impErr.o): ./impCommon.h
impList.o: ./impList.h
$(IMPLIB)(impList.o): ./impList.h
impList.o: ./impCommon.h
$(IMPLIB)(impList.o): ./impCommon.h
impScan.o: ./impScan.h
$(IMPLIB)(impScan.o): ./impScan.h
impScan.o: ./impCommon.h
$(IMPLIB)(impScan.o): ./impCommon.h
impScPaSema.o: ./impScan.h
$(IMPLIB)(impScPaSema.o): ./impScan.h
impScPaSema.o: ./impCommon.h
$(IMPLIB)(impScPaSema.o): ./impCommon.h
impScPaSema.o: ./impMacro.h
$(IMPLIB)(impScPaSema.o): ./impMacro.h
impScPaSema.o: ./impList.h
$(IMPLIB)(impScPaSema.o): ./impList.h
impScPaSema.o: ./impCommon.h
$(IMPLIB)(impScPaSema.o): ./impCommon.h
version.o: ./version.h
$(IMPLIB)(version.o): ./version.h
ast.o: ./impList.h
$(IMPLIB)(ast.o): ./impList.h
ast.o: ./impCommon.h
$(IMPLIB)(ast.o): ./impCommon.h
ast.o: ./impMacro.h
$(IMPLIB)(ast.o): ./impMacro.h
ast.o: ./name.h
$(IMPLIB)(ast.o): ./name.h
ast.o: ./ast.h
$(IMPLIB)(ast.o): ./ast.h
ast.o: ./impCommon.h
$(IMPLIB)(ast.o): ./impCommon.h
ast.o: ./impMacro.h
$(IMPLIB)(ast.o): ./impMacro.h
ast.o: ./ast.h
$(IMPLIB)(ast.o): ./ast.h
name.o: ./name.h
$(IMPLIB)(name.o): ./name.h
name.o: ./ast.h
$(IMPLIB)(name.o): ./ast.h
name.o: ./impCommon.h
$(IMPLIB)(name.o): ./impCommon.h
name.o: ./impMacro.h
$(IMPLIB)(name.o): ./impMacro.h
name.o: ./ast.h
$(IMPLIB)(name.o): ./ast.h
name.o: ./impScan.h
$(IMPLIB)(name.o): ./impScan.h
name.o: ./impCommon.h
$(IMPLIB)(name.o): ./impCommon.h
name.o: ./impList.h
$(IMPLIB)(name.o): ./impList.h
name.o: ./impCommon.h
$(IMPLIB)(name.o): ./impCommon.h
impMacro.o: ./impMacro.h
$(IMPLIB)(impMacro.o): ./impMacro.h
impMacro.o: ./impList.h
$(IMPLIB)(impMacro.o): ./impList.h
impMacro.o: ./impCommon.h
$(IMPLIB)(impMacro.o): ./impCommon.h
impMacro.o: ./impScan.h
$(IMPLIB)(impMacro.o): ./impScan.h
impMacro.o: ./impCommon.h
$(IMPLIB)(impMacro.o): ./impCommon.h
impMacro.o: ./ast.h
$(IMPLIB)(impMacro.o): ./ast.h
impMacro.o: ./impCommon.h
$(IMPLIB)(impMacro.o): ./impCommon.h
impMacro.o: ./impMacro.h
$(IMPLIB)(impMacro.o): ./impMacro.h
impMacro.o: ./timing.h
$(IMPLIB)(impMacro.o): ./timing.h
impMacro.o: ./version.h
$(IMPLIB)(impMacro.o): ./version.h
timing.o: ./timing.h
$(IMPLIB)(timing.o): ./timing.h
