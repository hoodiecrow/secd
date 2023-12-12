CC=clang
CFLAGS=-g -I. -W -Wall -Wextra -pedantic
DEPS=secd.h cons.h
OBJ=main.o read.o cons.o int.o print.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

secd: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) secd *~

