# Some common targets for all ToolMaker components

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
	@echo TMARCH=$(TMARCH)
