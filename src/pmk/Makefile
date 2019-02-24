# Makefile for ParserMaker
#
# This makefile is to compile directly from create sources
# without license...
#

TMARCH	= cygwin
mingw:	TMARCH	= mingw
mingw:	MINGW	= -mno-cygwin
mingw: CQ = -DMINGW
cygwin: CQ = -DCYGWIN

DEBUG	= -g

INCLUDE	= -I../tmk -I../imp

CFLAGS	= $(CQ) $(DEBUG) $(INCLUDE) $(MINGW)

LDFLAGS	= -lm $(LQ)

CC	= $(GCC)
CPP	= $(GCC)
GCC	= gcc -Wall

VERSIONOBJECTS = \
	pack.o \
	pmkErr.o \
	pmkList.o \
	pmkParse.o \
	pmkScan.o \
	pmkPaSema.o \
	pmkScSema.o \
	pmkSymTab.o \
	pmkTab.o \
	pwDbg.o \
	pwGe.o \
	pwLog.o \
	pwPack.o \
	pwSymSet.o \
	pwsGrm.o \
	pwsOrd.o \
	pwsQueue.o \
	pwsWrit.o \
	set.o \
	timing.o \
	pmk.o


OBJECTS = $(VERSIONOBJECTS) version.o

LIBS	= \
	../tmk/libtmk.a \
	../imp/imp.a


#--

all debug: tm pmkobj
	install -C -b Parse.imp Err.imp ../../lib/ansi-c

install: installdirs
	install -C Parse.imp Err.imp $(DESTLIB)/lib/ansi-c
	install pmk $(DESTROOT)/bin

tm:
	pmk pmk
	smk pmk
	lmk pmk

pmkobj: checkARCH $(TMARCH)
	install pmk ../../bin/

mingw cygwin sun3 sun4 solaris1 solaris2: ../license/license.h ../imp/impMacro.h ../tmk/tmk.h ../tmk/tmkCommon.h $(OBJECTS) $(LIBS)
	$(CC) -o pmk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS)

pmkParse.o: pmkParse.c
pmkPaSema.o: pmkPaSema.c
pmkErr.o: pmkErr.c
pmkScan.o: pmkScan.c
pmkScSema.o: pmkScSema.c
pmkList.o: pmkList.c

test:
	cd testing; make

#--
clean:
	rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt pmk

veryclean: clean
	rm pmk.voc pmkParse.* pmkScan.* pmkScSema.* pmkPaSema.* pmkCommon.h pmkList.* pmkErr.*

FILETER = | sed -e "\,/usr/include, d" | sort -u

depend file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJECTS:.o=.c) ; do $(CPP) $(INCLUDE) -M $$file | cat >> Makefile ; echo -n . ; done
	@echo "done."

include ../common.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
pack.o: pack.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h pack.h
pmkErr.o: pmkErr.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pws.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwsLexCode.h set.h pmk_i.h \
 /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pwSymSet.h \
 pwsGrm.h pmkSymTab.h pmkScan.h
pmkList.o: pmkList.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/xlocale.h /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/string.h /usr/include/strings.h \
 /usr/include/sys/string.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/ctype.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h
pmkParse.o: pmkParse.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pws.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwsLexCode.h set.h pmk_i.h \
 /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pwSymSet.h \
 pwsGrm.h pmkSymTab.h pmkScan.h /usr/include/setjmp.h \
 /usr/include/machine/setjmp.h pmkParse.h
pmkScan.o: pmkScan.c pws.h /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwsLexCode.h /usr/include/memory.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h /usr/include/malloc.h \
 /usr/include/machine/malloc.h pmkScan.h
pmkPaSema.o: pmkPaSema.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pws.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwsLexCode.h set.h pmk_i.h \
 /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pwSymSet.h \
 pwsGrm.h pmkSymTab.h pmkScan.h
pmkScSema.o: pmkScSema.c pws.h /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwsLexCode.h pmkScan.h \
 /usr/include/stdlib.h /usr/include/machine/stdlib.h \
 /usr/include/alloca.h /usr/include/cygwin/stdlib.h \
 /usr/include/cygwin/wait.h
pmkSymTab.o: pmkSymTab.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/string.h /usr/include/xlocale.h \
 /usr/include/strings.h /usr/include/sys/string.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h pmkList.h \
 pmkCommon.h ../tmk/tmkCommon.h pwsGrm.h pws.h ../tmk/tmk.h \
 ../tmk/tmkCommon.h pwSymSet.h set.h pmkSymTab.h
pmkTab.o: pmkTab.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pmk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h \
 pmkCommon.h ../tmk/tmkCommon.h /usr/include/fcntl.h \
 /usr/include/sys/fcntl.h /usr/include/sys/_default_fcntl.h \
 /usr/include/sys/stat.h /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pws.h pmkList.h \
 pwGe.h set.h pwPack.h pack.h pwsLexCode.h pwsGrm.h pwSymSet.h \
 pmkSymTab.h pwLog.h pmkParse.h version.h
pwDbg.o: pwDbg.c
pwGe.o: pwGe.c /usr/include/setjmp.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/machine/setjmp.h /usr/include/signal.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/include/sys/signal.h /usr/include/_ansi.h /usr/include/sys/types.h \
 /usr/include/machine/_types.h /usr/include/sys/_types.h \
 /usr/include/sys/lock.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/cygwin/signal.h /usr/include/sys/ucontext.h \
 /usr/include/stdio.h /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h pmk_i.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pmkCommon.h ../tmk/tmkCommon.h \
 /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h /usr/include/xlocale.h \
 /usr/include/cygwin/time.h /usr/include/cygwin/stat.h pws.h pmkList.h \
 set.h pwsGrm.h pwSymSet.h pmkSymTab.h pwLog.h pwGe.h
pwLog.o: pwLog.c /usr/include/string.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/include/sys/_types.h /usr/include/machine/_types.h \
 /usr/include/machine/_default_types.h /usr/include/sys/lock.h \
 /usr/include/sys/cdefs.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pmk_i.h /usr/include/stdio.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h ../tmk/tmk.h ../tmk/tmkCommon.h pmkCommon.h \
 ../tmk/tmkCommon.h /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pwsLexCode.h \
 pws.h pmkList.h pwLog.h pwsGrm.h pwSymSet.h set.h pmkSymTab.h pwsOrd.h \
 pwGe.h pwPack.h pack.h /usr/include/ctype.h
pwPack.o: pwPack.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h pmk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h \
 pmkCommon.h ../tmk/tmkCommon.h /usr/include/fcntl.h \
 /usr/include/sys/fcntl.h /usr/include/sys/_default_fcntl.h \
 /usr/include/sys/stat.h /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/xlocale.h /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pws.h pmkList.h \
 set.h pack.h pwGe.h pwsGrm.h pwSymSet.h pmkSymTab.h pwPack.h pwLog.h
pwSymSet.o: pwSymSet.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pws.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 ../tmk/tmk.h ../tmk/tmkCommon.h pwSymSet.h set.h pwsGrm.h pmkSymTab.h
pwsGrm.o: pwsGrm.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/ctype.h /usr/include/xlocale.h \
 /usr/include/string.h /usr/include/strings.h /usr/include/sys/string.h \
 /usr/include/stdlib.h /usr/include/machine/stdlib.h \
 /usr/include/alloca.h /usr/include/cygwin/stdlib.h \
 /usr/include/cygwin/wait.h /usr/include/unistd.h \
 /usr/include/sys/unistd.h /usr/include/getopt.h pmk_i.h ../tmk/tmk.h \
 ../tmk/tmkCommon.h pmkCommon.h ../tmk/tmkCommon.h /usr/include/fcntl.h \
 /usr/include/sys/fcntl.h /usr/include/sys/_default_fcntl.h \
 /usr/include/sys/stat.h /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pmkList.h \
 pwsGrm.h pws.h pwSymSet.h set.h pmkSymTab.h pwsLexCode.h pwsQueue.h \
 pwsOrd.h pwsWrit.h
pwsOrd.o: pwsOrd.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h pmkList.h pmkCommon.h ../tmk/tmkCommon.h \
 pmk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h /usr/include/fcntl.h \
 /usr/include/sys/fcntl.h /usr/include/sys/_default_fcntl.h \
 /usr/include/sys/stat.h /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h pwsGrm.h pws.h \
 pwSymSet.h set.h pmkSymTab.h
pwsQueue.o: pwsQueue.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h pmkList.h \
 pmkCommon.h ../tmk/tmkCommon.h pwsQueue.h pws.h ../tmk/tmk.h \
 ../tmk/tmkCommon.h pwsGrm.h pwSymSet.h set.h pmkSymTab.h
pwsWrit.o: pwsWrit.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h pwsGrm.h pws.h pmkList.h pmkCommon.h \
 ../tmk/tmkCommon.h ../tmk/tmk.h ../tmk/tmkCommon.h pwSymSet.h set.h \
 pmkSymTab.h pwsOrd.h pwGe.h
set.o: set.c /usr/include/string.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/include/sys/_types.h /usr/include/machine/_types.h \
 /usr/include/machine/_default_types.h /usr/include/sys/lock.h \
 /usr/include/sys/cdefs.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h set.h
timing.o: timing.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h timing.h /usr/include/malloc.h \
 /usr/include/machine/malloc.h /usr/include/sys/times.h
pmk.o: pmk.c /usr/include/stdio.h /usr/include/_ansi.h \
 /usr/include/newlib.h /usr/include/_newlib_version.h \
 /usr/include/sys/config.h /usr/include/machine/ieeefp.h \
 /usr/include/sys/features.h /usr/include/cygwin/config.h \
 /usr/include/sys/cdefs.h /usr/include/machine/_default_types.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stddef.h \
 /usr/lib/gcc/i686-pc-cygwin/7.4.0/include/stdarg.h \
 /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/sys/_types.h \
 /usr/include/machine/_types.h /usr/include/sys/lock.h \
 /usr/include/sys/types.h /usr/include/sys/_stdint.h \
 /usr/include/machine/endian.h /usr/include/machine/_endian.h \
 /usr/include/bits/endian.h /usr/include/sys/select.h \
 /usr/include/sys/_sigset.h /usr/include/sys/_timeval.h \
 /usr/include/sys/timespec.h /usr/include/sys/_timespec.h \
 /usr/include/sys/_pthreadtypes.h /usr/include/machine/types.h \
 /usr/include/endian.h /usr/include/bits/byteswap.h \
 /usr/include/bits/wordsize.h /usr/include/sys/sysmacros.h \
 /usr/include/sys/stdio.h /usr/include/stdlib.h \
 /usr/include/machine/stdlib.h /usr/include/alloca.h \
 /usr/include/cygwin/stdlib.h /usr/include/cygwin/wait.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/strings.h \
 /usr/include/sys/string.h timing.h /usr/include/malloc.h \
 /usr/include/machine/malloc.h /usr/include/sys/times.h ../tmk/tmk.h \
 ../tmk/tmkCommon.h pmk_i.h pmkCommon.h ../tmk/tmkCommon.h \
 /usr/include/fcntl.h /usr/include/sys/fcntl.h \
 /usr/include/sys/_default_fcntl.h /usr/include/sys/stat.h \
 /usr/include/time.h /usr/include/machine/time.h \
 /usr/include/cygwin/time.h /usr/include/signal.h \
 /usr/include/sys/signal.h /usr/include/cygwin/signal.h \
 /usr/include/sys/ucontext.h /usr/include/cygwin/stat.h version.h \
 pmkList.h pmkScan.h pwsGrm.h pws.h pwSymSet.h set.h pmkSymTab.h \
 ../imp/impMacro.h /usr/include/setjmp.h /usr/include/machine/setjmp.h
version.o: version.c version.h
