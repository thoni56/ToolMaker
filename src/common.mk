# Some common targets for all ToolMaker components

# So you can do <target>: <dependents> | ../../bin
../../bin:
	mkdir -p ../../bin

clean:
	rm -f *~ *.o *.d core *.pml *.sml *.smt *.pmt *.lmt *.gcov *.gcda

veryclean: clean
	rm -f *.voc *Parse.* *Scan.* *ScSema.* *PaSema.* *Common.h *List.* *Err.*

coverage: CFLAGS += --coverage
coverage: all
	$(MAKE) test
	-for f in *.o ; do gcov $$f 2>&1 >/dev/null | grep -v "assuming not executed" | grep -v "no functions found" ; done

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
