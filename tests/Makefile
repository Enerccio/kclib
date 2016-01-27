PREFIX?=
LIBDIR?=$(PREFIX)/lib
TARGET?=x86_64-test
MODE?=kernel
DEBREL?=debug

MACHINE != expr $(TARGET) : '\([^-]*\)-.*'
OS != expr $(TARGET) : '.*-\([^-]*\)'

include  ../kclib/$(DEBREL).mk
include  ../kclib/$(MODE).mk
include  ../kclib/machine/$(MACHINE).mk
-include ../kclib/$(MODE)/$(MACHINE)/$(OS)/defaults.mk
-include ../kclib/$(MODE)/$(MACHINE)/defaults.mk
-include ../kclib/$(MODE)/defaults.mk

CFLAGS:= -ffreestanding -std=c11 -Wall -Wextra \
	-fmessage-length=0 -nostdlib \
	 $(DEBREL_CFLAGS) $(MODE_CFLAGS) $(MACHINEDEF_CFLAGS) $(SYSDEF_CFLAGS) $(CFLAGS_FOR_TARGET) 
CPPFLAGS = $(MODE_CPPFLAGS) $(MACHINEDEF_CPPFLAGS) \
	$(DEBREL_CPPLAGS) $(SYSDEF_CPPFLAGS) $(CPPFLAGS_FOR_TARGET)
LDFLAGS = -nostdlib -static \
	$(DEBREL_LDFLAGS) $(MODE_LDFLAGS) $(MACHINEDEF_LDFLAGS) $(SYSDEF_LDFLAGS) $(LDFLAGS_FOR_TARGET) 
ASFLAGS := $(DEBREL_ASFLAGS) $(MODE_ASFLAGS) $(MACHINEDEF_ASFLAGS) $(SYSDEF_ASFLAGS) $(ASFLAGS_FOR_TARGET) 
AS := nasm

PASS := IPATH="../../include" CFLAGS="${CFLAGS}" CPPFLAGS="${CPPFLAGS}" LDFLAGS="${LDFLAGS}" ASFLAGS="${ASFLAGS}" AS="${AS}"

SUBDIRS := $(sort $(wildcard test_*/.))
SUBDIREXES := $(sort $(wildcard test_*/test))
SUBDIROS := $(sort $(wildcard test_*/*.o))

.PHONY: clean all compilebase cleanbase runtests $(SUBDIRS) $(SUBDIREXES)
	
all: runtests

cleanbase:
	$(MAKE) -C base clean

clean: cleanbase 
	-rm $(SUBDIROS)
	-rm $(SUBDIREXES)
	
compilebase:
	$(MAKE) -C base $(PASS)

compiletests: compilebase $(SUBDIRS)

$(SUBDIRS): 
	$(MAKE) -C $@ $(PASS)

runtests: compiletests $(SUBDIREXES)

$(SUBDIREXES):
	./$@