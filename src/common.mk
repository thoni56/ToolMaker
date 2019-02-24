#Some common targets for all ToolMaker components

# TODO: generate 'cygwin32' or 'cygwin64' and handle that in all skeleton files to
UNAME = ${shell uname}
TMARCH = ${if ${findstring CYGWIN,$(UNAME)},${if ${findstring WOW, $(UNAME)},cygwin32,cygwin64},${strip ${shell uname}}}

DESTROOT=/usr/local
DESTLIB=$(DESTROOT)/lib/ToolMaker

.PHONY: installdirs
installdirs:
	install -d $(DESTLIB)/lib/ansi-c
	ln -sf $(DESTLIB)/lib/ansi-c $(DESTLIB)/lib/c
	ln -sf $(DESTLIB)/lib/ansi-c $(DESTLIB)/lib/c++

checkARCH:
	@if test -f .arch ; then :; else echo "none" > .arch; fi
	@-if test "`cat .arch`" != "$(TMARCH)"; then \
		echo "Rebuilding for $(TMARCH)" ; \
		rm *.o *.a; \
		echo -n $(TMARCH) > .arch ; \
	fi

arch:
	echo TMARCH=$(TMARCH)
