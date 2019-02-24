#

all test tm install clean:
	cd tmk; make $@
	cd imp; make $@
	cd lmk; make $@
	cd smk; make $@
	cd pmk; make $@

arch:
	@echo TMARCH=$(TMARCH)

include common.mk
