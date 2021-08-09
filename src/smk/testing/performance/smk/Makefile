
#	Author : Tony Olsson
#	Date   : 1993-05-14/tools@wolf
#

.KEEP_STATE:

ROOT	=	/home/projects/ToolMaker
SHELL	=	/bin/sh

#
# Set these variables when compiling on apollo
#
#TMARCH	=	apollo
#TMHOME =

TMLIB	= /home/projects/ToolMaker/lib/c
TMBIN	= /home/projects/ToolMaker/bin/bin-$(TMARCH)

SMKQ	=
SMK	= ../../../smk $(SMKQ)

INCLUDE	=
LIBS    =
CFLAGS	= -O -DINLINE $(CQ) $(INCLUDE)
LDFLAGS	= -lm $(LQ)

CC	= gcc -traditional
CPP	=	/lib/cpp
MALLOCDEBUG	=
SMKFLAGS	=

OBJECTS	= pasScan.o pasScSema.o pas.o time.o

################################################################################
#
#

all: tm pas

################################################################################
#
#

tm: .smkStamp

.smkStamp: pas.tmk pas.smk pas.voc ../../../Scan.imp
	$(SMK) $(SMKFLAGS) pas
	touch .smkStamp

pas.voc:
	touch pas.voc



################################################################################
#
#

pas: $(OBJECTS) $(LIBS)
	$(CC) -o pas $(CFLAGS) $(OBJECTS) $(LIBS) $(LDFLAGS) $(MALLOCDEBUG)

#-

time.c: ../time/time.c
	rm -f time.c
	ln -s ../time/time.c time.c

time.h: ../time/time.h
	rm -f time.h
	ln -s ../time/time.h time.h

#--
clean:
	-rm -f *~ *.o core *.sm[tl] pas.voc pasScan.* pasScSema.* pasCommon.h Scan.imp Common.imp time.c time.h

veryclean: clean
	-rm -f pas

depend file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in $(OBJECTS:.o=.c) ; do \
	  $(CC) $(INCLUDE) -M $$file |\
	  awk 'NR == 1 {printf "%s %s",$$1,$$2;next} $$2 ~ /^[^/]/ {printf " %s",$$2} END {printf "\n"}' |\
	  sed 's, ./, ,g' |\
	  cat >> Makefile ; echo -n "." ; done
	@echo " done."

# DO NOT DELETE THIS LINE -- make depend depends on it.
pasScan.o: pasScan.c pasScan.h pasCommon.h
pasScSema.o: pasScSema.c pasScan.h pasCommon.h
pas.o: pas.c pasScan.h pasCommon.h time.h
time.o: time.c time.h
