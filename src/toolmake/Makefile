# Makefile for toolmake				  Date: 1993-06-21/reibert@roo
#
# Restored to working conditions thoni56/2022-02-05

include ../defines.mk

ROOT	= ../..
TMLIB	= $(ROOT)/lib/c/
TMBIN	= $(ROOT)/bin/bin
INTLIB	= $(ROOT)/library


INCLUDE	= -I../imp

LDFLAGS	= $(LQ) -lnsl

LIBS    = ../imp/imp.a

VERSIONOBJECTS = toolmake.o spa.o system.o ask.o menue.o

OBJECTS = $(VERSIONOBJECTS) version.o

debug	:= DEBUG=-g -DDBG
all		:= DEBUG=-O


.KEEP_STATE:

#--
all debug:	toolmake

toolmake: $(OBJECTS) $(LIBS)
	$(LINK.c) -o $@ $(OBJECTS) $(LIBS)
	cp *.imp $(TMLIB)

#--
clean:
	-rm *.o *~ core

veryclean: clean
	-rm toolmake

# EoF
