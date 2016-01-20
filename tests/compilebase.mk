SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEP    := $(SRC:.c=.d)
-include $(DEP)

clean:
	-rm -f *.o
	-rm -f *.d

%.o : %.c
	$(CC) -c ${CFLAGS} ${CPPFLAGS} -I$(IPATH) $< -MM -MF $(patsubst %.o,%.d,$@)
	$(CC) -c ${CFLAGS} ${CPPFLAGS} -I$(IPATH) $< -o $@