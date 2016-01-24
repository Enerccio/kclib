.PHONY: kclib clean crt0 tests

clean:
	$(MAKE) clean -C kclib
	$(MAKE) clean -C tests

all: kclib tests

kclib:
	$(MAKE) -C $@
	
crt0:
	$(MAKE) -C kclib $@ 

tests: compiletests runtests

compiletests:
	$(MAKE) -C kclib crt0
	$(MAKE) -C tests compiletests
	
runtests:
	$(MAKE) -C tests runtests 