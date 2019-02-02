#	Makefile for ScannerMaker
#
#	This makefile is for compiling from existing sources
#	without license

TMARCH	= cygwin
mingw:	TMARCH = mingw
mingw:	MINGW	= -mno-cygwin
cygwin: CQ = -DCYGWIN

#CQ	= -DWIN32

INCLUDE	= -I../tmk -I../imp

CFLAGS	= $(CQ) -Wall $(INCLUDE) $(MINGW)

LIBS    = ../tmk/libtmk.a ../imp/imp.a
LDFLAGS	= $(LQ)

CC	= $(GCC)

GCC	= gcc

VERSIONOBJECTS	= smkPaSema.o smkScSema.o smkParse.o smkErr.o smkScan.o smkList.o smk.o token.o \
	scanner.o vocabulary.o definition.o rule.o ast.o lmprintf.o name.o char.o nfa.o \
	lookahead.o dfa.o map.o pack.o write.o time.o \
	action.o set.o screen.o smalloc.o nfas.o common.o

OBJECTS		= $(VERSIONOBJECTS) version.o


test:
	cd testing; jregr

################################################################################
#
#
all debug : smkobj

################################################################################
#
#

smkobj: checkARCH $(TMARCH)
	cp smk.exe ../../bin/

mingw cygwin sun3 sun4 solaris1 solaris2: $(OBJECTS) $(LIBS)
	$(CC) -o smk $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS) $(MALLOCDEBUG)


#--
clean:
	-rm -f *~ *.o core *.pml *.sml *.smt *.pmt *.lmt smk.voc smkParse.* smkScan.* \
	smkScSema.* smkPaSema.* smkCommon.h smkList.* smkErr.* .stamp_???

veryclean: clean
	-rm -f smk

depend file: depend.gcc

depend.gcc:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJECTS:.o=.c) ; do $(CC) $(INCLUDE) -MM $$file >> Makefile 2> /dev/null ; echo -n "." ; done
	@echo " done."

include ../common.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
smkPaSema.o: smkPaSema.c common.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h definition.h map.h set.h smkScan.h smkCommon.h smkList.h \
  smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h
smkScSema.o: smkScSema.c common.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h set.h smkScan.h smkCommon.h smalloc.h smkList.h smk_i.h \
  ../tmk/tmk.h ../tmk/tmkCommon.h
smkParse.o: smkParse.c common.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h definition.h map.h set.h smkScan.h smkCommon.h smkList.h \
  smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h smkParse.h
smkErr.o: smkErr.c common.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h definition.h map.h set.h smkScan.h smkCommon.h smkList.h \
  smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h
smkScan.o: smkScan.c common.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h set.h smkScan.h smkCommon.h smalloc.h smkList.h smk_i.h \
  ../tmk/tmk.h ../tmk/tmkCommon.h
smkList.o: smkList.c smkList.h smkCommon.h common.h ../tmk/tmkCommon.h \
  name.h action.h token.h vocabulary.h scanner.h rule.h ast.h lookahead.h \
  nfas.h nfa.h dfa.h pack.h
smk.o: smk.c ../imp/impMacro.h common.h char.h dfa.h pack.h nfas.h nfa.h \
  rule.h ../tmk/tmkCommon.h scanner.h vocabulary.h name.h token.h ast.h \
  lookahead.h action.h map.h screen.h set.h smkScan.h smkCommon.h \
  smalloc.h smkList.h smkParse.h smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h \
  time.h version.h write.h
token.o: token.c common.h smalloc.h token.h ../tmk/tmkCommon.h \
  vocabulary.h name.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h \
  dfa.h pack.h action.h
scanner.o: scanner.c common.h scanner.h ../tmk/tmkCommon.h vocabulary.h \
  name.h token.h rule.h ast.h lookahead.h nfas.h nfa.h dfa.h pack.h \
  action.h smalloc.h smkList.h smkCommon.h smk_i.h ../tmk/tmk.h \
  ../tmk/tmkCommon.h
vocabulary.o: vocabulary.c common.h lmprintf.h smalloc.h smkList.h \
  smkCommon.h ../tmk/tmkCommon.h name.h action.h token.h vocabulary.h \
  scanner.h rule.h ast.h lookahead.h nfas.h nfa.h dfa.h pack.h smkScan.h \
  smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h
definition.o: definition.c definition.h name.h ast.h action.h token.h \
  ../tmk/tmkCommon.h vocabulary.h common.h scanner.h rule.h lookahead.h \
  nfas.h nfa.h dfa.h pack.h lmprintf.h smalloc.h smkList.h smkCommon.h \
  smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h
rule.o: rule.c common.h lmprintf.h ast.h name.h rule.h ../tmk/tmkCommon.h \
  scanner.h vocabulary.h token.h nfas.h nfa.h dfa.h pack.h lookahead.h \
  action.h smalloc.h smkList.h smkCommon.h smk_i.h ../tmk/tmk.h \
  ../tmk/tmkCommon.h
ast.o: ast.c ast.h name.h char.h common.h lmprintf.h smalloc.h smkList.h \
  smkCommon.h ../tmk/tmkCommon.h action.h token.h vocabulary.h scanner.h \
  rule.h lookahead.h nfas.h nfa.h dfa.h pack.h
lmprintf.o: lmprintf.c common.h lmprintf.h smkList.h smkCommon.h \
  ../tmk/tmkCommon.h name.h action.h token.h vocabulary.h scanner.h \
  rule.h ast.h lookahead.h nfas.h nfa.h dfa.h pack.h
name.o: name.c smkList.h smkCommon.h common.h ../tmk/tmkCommon.h name.h \
  action.h token.h vocabulary.h scanner.h rule.h ast.h lookahead.h nfas.h \
  nfa.h dfa.h pack.h smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h smalloc.h \
  lmprintf.h
char.o: char.c smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h name.h char.h \
  map.h smalloc.h set.h smkScan.h smkCommon.h common.h ../tmk/tmkCommon.h \
  action.h token.h vocabulary.h scanner.h rule.h ast.h lookahead.h nfas.h \
  nfa.h dfa.h pack.h
nfa.o: nfa.c ast.h name.h char.h lmprintf.h lookahead.h rule.h common.h \
  ../tmk/tmkCommon.h scanner.h vocabulary.h token.h nfas.h nfa.h dfa.h \
  pack.h action.h smalloc.h smkList.h smkCommon.h smk_i.h ../tmk/tmk.h \
  ../tmk/tmkCommon.h
lookahead.o: lookahead.c ast.h name.h lookahead.h rule.h common.h \
  ../tmk/tmkCommon.h scanner.h vocabulary.h token.h nfas.h nfa.h dfa.h \
  pack.h action.h smalloc.h
dfa.o: dfa.c char.h dfa.h pack.h nfas.h nfa.h common.h rule.h \
  ../tmk/tmkCommon.h scanner.h vocabulary.h name.h token.h ast.h \
  lookahead.h action.h lmprintf.h map.h set.h smkScan.h smkCommon.h \
  smalloc.h smkList.h smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h
map.o: map.c char.h lmprintf.h map.h smkList.h smkCommon.h common.h \
  ../tmk/tmkCommon.h name.h action.h token.h vocabulary.h scanner.h \
  rule.h ast.h lookahead.h nfas.h nfa.h dfa.h pack.h smk_i.h ../tmk/tmk.h \
  ../tmk/tmkCommon.h
pack.o: pack.c smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h name.h pack.h
write.o: write.c smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h name.h pack.h \
  action.h token.h ../tmk/tmkCommon.h vocabulary.h common.h scanner.h \
  rule.h ast.h lookahead.h nfas.h nfa.h dfa.h set.h smkScan.h smkCommon.h \
  map.h version.h screen.h smalloc.h lmprintf.h
time.o: time.c time.h
action.o: action.c smalloc.h action.h token.h ../tmk/tmkCommon.h \
  vocabulary.h common.h name.h scanner.h rule.h ast.h lookahead.h nfas.h \
  nfa.h dfa.h pack.h
set.o: set.c smk_i.h ../tmk/tmk.h ../tmk/tmkCommon.h name.h set.h \
  smkScan.h smkCommon.h common.h ../tmk/tmkCommon.h action.h token.h \
  vocabulary.h scanner.h rule.h ast.h lookahead.h nfas.h nfa.h dfa.h \
  pack.h char.h smkList.h lmprintf.h
screen.o: screen.c ast.h name.h common.h rule.h ../tmk/tmkCommon.h \
  scanner.h vocabulary.h token.h nfas.h nfa.h dfa.h pack.h lookahead.h \
  action.h screen.h set.h smkScan.h smkCommon.h smalloc.h
smalloc.o: smalloc.c common.h smalloc.h
nfas.o: nfas.c common.h smalloc.h lmprintf.h nfa.h nfas.h rule.h \
  ../tmk/tmkCommon.h scanner.h vocabulary.h name.h token.h dfa.h pack.h \
  ast.h lookahead.h action.h
common.o: common.c
version.o: version.c version.h
