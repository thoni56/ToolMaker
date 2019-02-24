#

all test tm install clean:
	cd tmk; make $@
	cd imp; make $@
	cd lmk; make $@
	cd smk; make $@
	cd pmk; make $@

archs:
	for f in */.arch ; do echo -n $$f=; cat $$f; echo ; done

include common.mk
