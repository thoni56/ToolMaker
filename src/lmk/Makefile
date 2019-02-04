# Makefile for lmk
#
# This Makefile is for compiling from existing sources only
# without license
#

DESTROOT = /usr/local

TMARCH	= cygwin
mingw:	TMARCH	= mingw
mingw:	MINGW	= -mno-cygwin

#CQ	= -DWIN32

INCLUDE	= -I../tmk -I../imp
LDFLAGS	= -lm $(LQ)

LIBS    = ../tmk/libtmk.a ../imp/imp.a

CC = $(GCC)
GCC = gcc

CFLAGS = $(CQ) -Wall $(INCLUDE) $(MINGW)

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
# Normal compilation
all debug opt: lmkobj
	install -C List.imp ../../lib/ansi-c

test:
	cd testing; jregr

install:
	install -d $(DESTROOT)/lib/ToolMaker/ansi-c
	ln -sf $(DESTROOT)/lib/ToolMaker/ansi-c $(DESTROOT)/lib/ToolMaker/c
	ln -sf $(DESTROOT)/lib/ToolMaker/ansi-c $(DESTROOT)/lib/ToolMaker/c++
	install	-C List.imp $(DESTROOT)/lib/ToolMaker/ansi-c
	install lmk $(DESTROOT)/bin

# Miscellaneous targets down here

lmkobj : checkARCH $(TMARCH)
	install lmk ../../bin/

cygwin mingw sun3 sun4 solaris1 solaris2: ../license/license.h ../imp/impMacro.h ../tmk/tmk.h ../tmk/tmkCommon.h $(OBJECTS) $(LIBS)
	$(CC) -o lmk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS)

#--
clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt lmk

veryclean: clean
	rm -f lmk.voc lmkParse.* lmkScan.* lmkScSema.* lmkPaSema.* lmkCommon.h lmkList.* lmkErr.*

FILETER = | sed -e "\,/usr/include, d" | sort -u

depend file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJECTS:.o=.c) ; do /lib/cpp $(INCLUDE) -M $$file | egrep -v '/usr/include|\.c$$' | cat >> Makefile ; echo -n . ; done
	@echo "done."

lmkParse.o: lmkParse.c
lmkPaSema.o: lmkPaSema.c
lmkErr.o: lmkErr.c
lmkScan.o: lmkScan.c
lmkScSema.o: lmkScSema.c
lmkList.o: lmkList.c

include ../common.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
