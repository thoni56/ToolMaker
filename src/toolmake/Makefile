# Makefile for toolmake			      Date: 1993-06-21/reibert@roo
#

ROOT	= /home/projects/ToolMaker
TMLIB	= $(ROOT)/lib/c/
TMBIN	= $(ROOT)/bin/bin-$(TMARCH)
INTLIB	= $(ROOT)/library

SUN3	= slug

RELEASEROOT	= $(ROOT)
RELEASELIB	= $(RELEASEROOT)/lib/c/
RELEASEBIN	= $(RELEASEROOT)/bin/bin-$(TMARCH)/
RELEASEMAN	= $(RELEASEROOT)/man/man1


CC	= gcc
CFLAGS	=\
	'-DTMHOME="/usr/local/ToolMaker"'\
	$(DEBUG) $(CQ) $(INCLUDE)
INCLUDE	= -I../license -I../imp

LDFLAGS	= $(LQ) -lnsl

LIBS    = ../license/license.o ../imp/imp.a

VERSIONOBJECTS = toolmake.o spa.o system.o ask.o menue.o
VQ	= +t

OBJECTS = $(VERSIONOBJECTS) version.o

debug 	:= DEBUG=-g -DDBG
all 	:= DEBUG=-O
release releaseARCH RELEASE := DEBUG=-O

.KEEP_STATE:

#--
all debug: 	toolmake

toolmake: init checkARCH $(OBJECTS) $(LIBS)
	$(LINK.c) -o $@ $(OBJECTS) $(LIBS)

init: ../license/license.h ../imp/impMacro.h version.h

checkARCH:
	if test -f .arch ; then :; else echo "none" > .arch; fi
	-if test `cat .arch` != $(TMARCH); then \
	    rm *.o; \
	    echo $(TMARCH) > .arch ; \
	fi

#--
release:
	@if cvs status | egrep Status | egrep -v Up-to-date ; then \
		exit 1 ; \
	fi
	make newversion releaseARCH releaseSRC
	cvs rtag toolmake`ls [0-9]*_[0-9]*_[0-9]*.* | sed s/\\\.//` toolmake

releaseSRC:
	for f in *.imp; \
	  do \
	    install -m 664 $$f $(RELEASELIB); \
	done
	install -m 664 toolmake.1 $(RELEASEMAN)

releaseARCH: toolmake
	install -s -m 775 toolmake $(RELEASEBIN)

RELEASE:
	@if test -r CVS/Tag ; then \
	  : ; \
	else \
	  echo This tree is not checked out from a Tag! ; \
	  echo RELEASE not allowed!! ; \
	  exit 1 ; \
	fi
	@if cvs status | egrep Status | egrep -v Up-to-date ; then \
		exit 1 ; \
	fi
	make newversion releaseARCH releaseSRC

#--
../license/license.h: $(INTLIB)/license.h
	@-[ ! -d ../license ] && mkdir ../license
	cp -p $(INTLIB)/license.h ../license/license.h

../license/license.o: $(INTLIB)/bin-$(TMARCH)/license.o
	@-[ ! -d ../license ] && mkdir ../license
	cp -p $(INTLIB)/bin-$(TMARCH)/license.o ../license/license.o

#--
../imp/imp.a: $(INTLIB)/bin-$(TMARCH)/imp.a
	@-[ ! -d ../imp ] && mkdir ../imp
	cp -p $(INTLIB)/bin-$(TMARCH)/imp.a ../imp/imp.a

../imp/impMacro.h: $(INTLIB)/impMacro.h
	@-[ ! -d ../imp ] && mkdir ../imp
	cp -p $(INTLIB)/impMacro.h ../imp

#--
version.c: $(VERSIONOBJECTS)
	-@rm [0-9]*_[0-9]*_[0-9]*.*
	@sh version.sh
	venum $(VQ)

version.h:
	-@rm [0-9]*_[0-9]*_[0-9]*.*
	@sh version.sh
	venum $(VQ) -c

newversion:
	-@rm [0-9]*_[0-9]*_[0-9]*.*
	@sh version.sh
	venum +c
	@echo "cat > `ls [0-9]*_[0-9]*_[0-9]*.*` <<EOF" > version.sh
	@echo "toolmake" >> version.sh
	@echo "initiator for ToolMaker tools" >> version.sh
	@echo "EOF" >> version.sh
	cvs commit -m 'New Version' version.sh

#--
clean:
	-rm *.o *~ core

veryclean: clean
	-rm toolmake

# EoF
