#Some common targets for all ToolMaker components

# TODO: generate 'cygwin32' or 'cygwin64' and handle that in all skeleton files to
TMARCH = ${if ${findstring CYGWIN, ${shell uname}},Cygwin,${strip ${shell uname}}}

checkARCH:
	@if test -f .arch ; then :; else echo "none" > .arch; fi
	@-if test "`cat .arch`" != "$(TMARCH)"; then \
		echo "Rebuilding for $(TMARCH)" ; \
		rm *.o *.a; \
		echo -n $(TMARCH) > .arch ; \
	fi
