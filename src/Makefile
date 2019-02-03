#
TMARCH	= ${if ${findstring CYGWIN, ${shell uname}},cygwin,${strip ${shell uname}}}

all: tmk imp lmk smk pmk

.PHONY: tmk
tmk:
	cd tmk; make TMARCH=$(TMARCH)

.PHONY: imp
imp:
	cd imp; make TMARCH=$(TMARCH)

.PHONY: lmk
lmk:
	cd lmk; make TMARCH=$(TMARCH)

.PHONY: smk
smk:
	cd smk; make TMARCH=$(TMARCH)

.PHONY: pmk
pmk:
	cd pmk; make TMARCH=$(TMARCH)

test:
	cd imp; make test
	cd lmk; make test
	cd smk; make test
	cd pmk; make test

clean:
	cd tmk; make clean
	cd imp; make clean
	cd lmk; make clean
	cd smk; make clean
	cd pmk; make clean

arch:
	@echo TMARCH=$(TMARCH)
