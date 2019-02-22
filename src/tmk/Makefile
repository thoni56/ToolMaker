# Makefile for tmk
#
# This makefile is to make from already existing sources

DESTROOT=/usr/local

TMARCH	= cygwin
mingw:	TMARCH	= mingw
mingw:	MINGW	= -mno-cygwin
mingw: CQ = -DMINGW
cygwin: CQ = -DCYGWIN

DEBUG	= -g

LIB     = libtmk.a

LDFLAGS	= $(LQ)

CC = gcc -Wall
CFLAGS	= $(DEBUG) $(CQ) $(MINGW)

SRCS.c= tmkPaSema.c tmkParse.c tmkErr.c tmkScan.c tmkScSema.c tmkOpts.c tmkCommon.c

OBJS.c= ${SRCS.c:.c=.o}
OBJS=   $(OBJS.c)

.PRECIOUS: $(LIB)

#--
all debug: $(TMARCH)
	install -C -b Common.imp ../../lib/ansi-c

# Install in DESTROOT/bin, DESTROOT/lib/ToolMaker=DESTLIB & DESTROOT/man
install: installdirs
	install -C Common.imp $(DESTLIB)/lib//ansi-c

.PHONY: $(TMARCH)
$(TMARCH): tmkobj

$(LIB): $(OBJS)
	ar r $(LIB) $?
	-ranlib $(LIB)

tmkobj: checkARCH $(LIB) version.c
	-ranlib $(LIB)

tmkParse.o: tmkParse.c
tmkPaSema.o: tmkPaSema.c
tmkErr.o: tmkErr.c
tmkScan.o: tmkScan.c
tmkScSema.o: tmkScSema.c
tmkList.o: tmkList.c

#--
clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt $(LIB)

depend file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJS:.o=.c) ; do /lib/cpp $(INCLUDE) -M $$file | egrep -v '/usr/include|\.c$$' | cat >> Makefile ; echo -n . ; done
	@echo "done."

include ../common.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
