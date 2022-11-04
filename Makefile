CC= gcc
CFLAGS=-Wall -std=c99 -D_GNU_SOURCE

TARGETS = acs

.PHONY: all clean

OBJ = $(patsubst %,obj/%.o,$(TARGETS))
SRC = ./%.c

all: acs 

obj/%.o: $(SRC) | obj
	$(CC) -c -o $@ $< $(CFLAGS)

obj:
	mkdir -p $@

acs: $(OBJ)
	$(CC) -o acs $^ $(CFLAGS) 

debug: CFLAGS += -g
debug: acs

clean:
	-rm -rf obj/ acs
