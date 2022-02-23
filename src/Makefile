#

all test tm install clean:
	cd tmk; make $@
	cd imp; make $@
	cd lmk; make $@
	cd pmk; make $@
	cd smk; make $@

archs:
	for f in */.arch ; do echo -n $$f=; cat $$f; echo ; done
