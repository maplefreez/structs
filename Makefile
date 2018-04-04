CC=gcc
CFLAGS=-g

all: lstring

lstring: lstring.c lstring.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f lstring.o

