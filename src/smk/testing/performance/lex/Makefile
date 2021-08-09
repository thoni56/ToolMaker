#
# AUTHOR : Tony Olsson
# DATE   : 1993-04-21/tools@lion
# CREATED: 1990-07-12
#
# SoftLab ab (c) 1990
#

.KEEP_STATE:

SHELL	=	/bin/sh

CFLAGS	= -O
CC	= gcc -traditional

OBJECTS	= lex.yy.o pas.o time.o

################################################################################
#
#

pas: $(OBJECTS)
	$(CC) -o pas $(CFLAGS) $(OBJECTS) -ll

lex.yy.c: pas.lex
	lex -f pas.lex

time.c: ../time/time.c
	ln -s ../time/time.c time.c

time.h: ../time/time.h
	ln -s ../time/time.h time.h

#---

clean:
	-rm -f core *~ lex.yy.c *.o time.h time.c

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
lex.yy.o :
pas.o :
time.o :

