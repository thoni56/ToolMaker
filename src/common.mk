#Some common targets for all ToolMaker components

checkARCH:
	if test -f .arch ; then :; else echo "none" > .arch; fi
	-if test "`cat .arch`" != "$(TMARCH)"; then \
	    rm *.o *.a; \
	    echo -n $(TMARCH) > .arch ; \
	fi

