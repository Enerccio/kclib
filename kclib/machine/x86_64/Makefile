ASMSRC := $(wildcard *.s)
SRC    := $(wildcard *.c)
OBJ    := $(SRC:.c=.o) $(ASMSRC:.s=_o.o)
DEP    := $(SRC:.c=.d)
-include $(DEP)

.PHONY: all clean 

all: $(OBJ)

clean:
	-rm -f $(OBJ)
	-rm -f $(wildcard *.d)

%.o : %.c 
	$(CC) -MM -MF $(patsubst %.o,%.d,$@) $(CFLAGS) $(CPPFLAGS) -c $< 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%_o.o : %.s 
	$(AS) $(ASFLAGS) $< -o $@

