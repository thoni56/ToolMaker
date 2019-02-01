#
# AUTHOR: Tony Olsson
# DATE: 1993-08-20/tony@wolf
# CREATE: 1990-04-11
#
# SoftLab ab (c) 1990
#

ROOT	=	/home/projects/ToolMaker
RELEASEROOT	= $(ROOT)
SHELL	=	/bin/sh

#
# Set these variables when compiling on apollo
#
#TMHOME	= 	..
#TMARCH	=	apollo

SERVER	=	rpc.toolmaker
CLIENT	=	client
PASSWD	=	tmpasswd
LICENSE	=	license.o

INTLIB	=	$(ROOT)/library

CC	=	$(GCC) -ansi -pedantic -Wall
GCC	=	gcc
#solaris1 sun4:=		GCC=	gcc2.5.7
solaris2:=	GCC=	gcc2.7.2

CPP	=	/lib/cpp
INCLUDE	=	-I../license
LDFLAGS	=	-lnsl
solaris1 sun4:=	LDFLAGS	=	-lnsl -L/usr/local/lib/4.1.2

SERVEROBJECTS	= license_rpc_svc.o readParam.o passwd.o version.o common.o licenseServer.o 
CLIENTOBJECTS	= client.o
PASSWDOBJECTS	= getpasswd.o passwd.o version.o
LICENSEOBJECTS	= licenseClient.o readParam.o passwd.o common.o
VERSIONSRCS	= licenseServer.c license_rpc_svc.c readParam.c passwd.c client.c getpasswd.c licenseClient.c common.c
VERSIONOBJECTS	= ${VERSIONSRCS:.c=.o}

all	:= CFLAGS= -O4 $(CQ) $(INCLUDE) 
purify debug	:= CFLAGS= -g $(CQ) $(INCLUDE)
release := CFLAGS= -O4 $(CQ) $(INCLUDE)
releaseARCH := CFLAGS= -O4 $(CQ) $(INCLUDE)
RELEASE := CFLAGS= -O4 $(CQ) $(INCLUDE)

################################################################################
#
#


.KEEP_STATE:

all debug:  licenseobj

purify: purify_server purify_client

clean:
	-rm -f *.o *~ core license_rpc_svc.c license_rpc_clnt.c license_rpc.h license_rpc_svc_tmp.c .make_state

veryclean: clean
	-rm -f $(SERVER) $(CLIENT) $(PASSWD) $(LICENSE)

file:
	@echo -n "Make depend "
	@mv Makefile Makefile.~
	@sed -n '1,/^# DO NOT DELETE THIS LINE -- make depend depends on it.$$/ p' Makefile.~ > Makefile
	@for file in *.c ; do /lib/cpp $(INCLUDE) -M $$file | egrep -v '/usr/include' | cat >> Makefile ; echo -n . ; done
	@echo " done."

release:
	@if cvs status | egrep Status | egrep -v Up-to-date ; then \
		exit 1 ; \
	fi
	make newversion releaseARCH releaseSRC
	cvs rtag license`ls [0-9]*_[0-9]*_[0-9]*.* | sed s/\\\.//` license

releaseSRC:
	chmod 664 license.h
	-rm -f $(INTLIB)/license.h
	cp -p license.h $(INTLIB)

releaseARCH: licenseobj
	chmod 664 license.o
	-rm -f $(INTLIB)/bin-$(TMARCH)/license.o
	cp -p license.o $(INTLIB)/bin-$(TMARCH)/
	install -s -m 775 $(SERVER) $(RELEASEROOT)/bin/bin-$(TMARCH)/$(SERVER)
	install -s -m 775 $(PASSWD) $(INTLIB)/bin-$(TMARCH)/$(PASSWD)

newversion:
	@-\rm [0-9]*_[0-9]*_[0-9]*.*
	@sh version.sh
	venum +c
	echo "cat > `ls [0-9]*_[0-9]*_[0-9]*.*` <<EOF" > version.sh
	echo "License Server" >> version.sh
	echo "ToolMaker License Server" >> version.sh
	echo "EOF" >> version.sh
	cvs commit -m 'New Version' version.sh

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
	make releaseARCH releaseSRC


################################################################################
#
#

licenseobj: checkARCH $(TMARCH)

checkARCH:
	if test -f .arch ; then :; else echo "none" > .arch; fi
	-if test `cat .arch` != $(TMARCH); then \
	    make clean; \
	    $(MAKE) rpc; \
	    echo $(TMARCH) > .arch ; \
	fi

sun4 solaris1 solaris2:	$(LICENSE) $(SERVER) $(CLIENT) $(PASSWD)
apollo: 	$(LICENSE) $(CLIENT) $(PASSWD)

$(SERVER): $(SERVEROBJECTS)
	$(CC) -o $(SERVER) $(CFLAGS) $(SERVEROBJECTS) $(LDFLAGS)

purify_server: $(SERVEROBJECTS)
	purify $(CC) -o $(SERVER) $(CFLAGS) $(SERVEROBJECTS) $(LDFLAGS)


$(CLIENT): $(CLIENTOBJECTS) $(LICENSE)
	$(CC) -o $(CLIENT) $(CFLAGS) $(CLIENTOBJECTS) $(LICENSE) $(LDFLAGS)

purify_client: $(CLIENTOBJECTS)
	purify $(CC) -o $(CLIENT) $(CFLAGS) $(CLIENTOBJECTS) $(LICENSE) $(LDFLAGS)

$(PASSWD): $(PASSWDOBJECTS)
	$(CC) -o $(PASSWD) $(CFLAGS) $(PASSWDOBJECTS)

license.o: $(LICENSEOBJECTS) license_rpc_clnt.o
	$(LD) -r -o $(LICENSE) $(LICENSEOBJECTS) license_rpc_clnt.o

license_rpc_clnt.o: license_rpc_clnt.c
	$(CC) $(CLAGS) -c license_rpc_clnt.c

license_rpc_clnt.c: license_rpc.x
	make rpc

obj-apollo/license.o: $(LICENSEOBJECTS)
	$(LD) -r -o $(LICENSE) $(LICENSEOBJECTS)

#license_rpc_svc.c + license_rpc_clnt.c + license_rpc.h: license_rpc.x
# We must force the rpcgeneration on the target system!!!
rpc:
	rpcgen license_rpc.x
	@echo "Modifying license_rpc_svc.c ..."
	@mv license_rpc_svc.c license_rpc_svc_tmp.c
	@sed -e 's/svc_run();/licenseInit(argc,argv);licenseDelay();svc_run();/' license_rpc_svc_tmp.c |\
	 sed -e 's/main()/int main(argc,argv) int argc;char **argv;/' > license_rpc_svc.c
	@rm license_rpc_svc_tmp.c

version.c version.h: $(VERSIONSRCS)
	@-\rm [0-9]*_[0-9]*_[0-9]*.*
	sh version.sh
	venum +t

# DO NOT DELETE THIS LINE -- make depend depends on it.
