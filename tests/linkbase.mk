test: $(OBJ)
	$(LD) -o $@ $(wildcard ../base/*.o) $(OBJ) -nostdlib ../../lib/crt0.o ../../lib/crti.o ../../lib/crtn.o \
		$(LDFLAGS) -L../../lib -lc  