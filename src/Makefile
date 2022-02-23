#

.PHONY: coverage
all test tm install clean coverage:
	cd tmk; make $@
	cd imp; make $@
	cd lmk; make $@
	cd pmk; make $@
	cd smk; make $@

archs:
	for f in */.arch ; do echo -n $$f=; cat $$f; echo ; done

report: coverage
	lcov -q -c -d . -o tm.info
	genhtml -q tm.info -o coverage/
	# open/xdg-open coverage/index.html
