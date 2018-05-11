CC=gcc
CFLAGS=-g
TESTS=t_lstring t_btree
OBJS=lstring.o btree.o

all: $(OBJS) $(TESTS)

test:	$(TESTS)

t_lstring:	t_lstring.c lstring.o
	$(CC) -o $@ $^ $(CFLAGS)

t_btree:	t_btree.c btree.o
	$(CC) -o $@ $^ $(CFLAGS)

lstring.o: lstring.c lstring.h
	$(CC) -c $< $(CFLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(TESTS) $(OBJS)

