# Makefile for af			Date: 1997-01-20/toolmake
#
# ToolMaker tools must be accessible via the PATH environment variable.
#
# The various *Q-macros are intended for commandline additions to the
# make invocation.
#
# The environmental variable TMHOME should be set to the ToolMaker
# home library, eg /usr/local/ToolMaker

IMP	= imp $(IMPQ)
PMK	= pmk $(PMQ)
SMK	= smk $(SMQ)
LMK	= lmk $(LMQ)

LDFLAGS	= $(LQ)

CC = acc -Xc
CFLAGS = $(DEBUG) $(CQ)

OBJECTS = \
	af.o \
	afPaSema.o afParse.o \
	afErr.o \
	afScan.o afScSema.o \
	afList.o

.KEEP_STATE:

#--
all debug: ToolMaker af

debug:=	DEBUG= -g

all:=	DEBUG= -O

#--
af: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

#--
ToolMaker: .pmkstamp .smkstamp .lmkstamp

.pmkstamp: af.pmk af.tmk
	$(PMK) af
	@touch .pmkstamp

.smkstamp: af.smk af.tmk af.voc
	$(SMK) af
	@touch .smkstamp

.lmkstamp: af.lmk af.tmk
	$(LMK) af
	@touch .lmkstamp


#-- Take care of disappeared files
afCommon.h:
	@touch af.tmk
	make ToolMaker

afParse.c + afParse.h + afPaSema.c + afErr.c + af.voc:
	@touch af.pmk
	make .pmkstamp

afScan.c + afScan.h + afScSema.c:
	@touch af.smk
	make .smkstamp

afList.c + afList.h:
	@touch af.lmk
	make .lmkstamp

#-- Dependencies between generated files
afErr.o: afErr.c afCommon.h afList.h afScan.h
afParse.o: afParse.c afCommon.h afParse.h afScan.h
afPaSema.o: afPaSema.c afCommon.h afScan.h
afScan.o: afScan.c afCommon.h afScan.h
afScSema.o: afScSema.c afCommon.h afScan.h
afList.o: afList.c afCommon.h afList.h

#--
clean:
	-rm *.o core  *.pml *.sml


#-- EoF --

