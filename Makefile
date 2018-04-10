CC=gcc
CFLAGS=-g
TESTS=t_lstring
OBJS=lstring.o

all: $(OBJS) $(TESTS)

test:	$(TESTS)

t_lstring:	t_lstring.c lstring.o
	$(CC) -o $@ $^ $(CFLAGS)

lstring.o: lstring.c lstring.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(TESTS) $(OBJS)

