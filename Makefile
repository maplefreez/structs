CC=gcc
CFLAGS=-g -Wno-int-to-pointer-cast
TESTS=t_lstring t_btree t_bstree
OBJS=lstring.o btree.o bstree.o stack.o

all: $(OBJS) $(TESTS)

test:	$(TESTS)

t_lstring:	t_lstring.c lstring.o
	$(CC) -o $@ $^ $(CFLAGS)

t_btree:	t_btree.c btree.o
	$(CC) -o $@ $^ $(CFLAGS)

t_bstree: t_bstree.c btree.o bstree.o
	$(CC) -o $@ $^ $(CFLAGS)

lstring.o: lstring.c lstring.h
	$(CC) -c $< $(CFLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(CFLAGS)

bstree.o: bstree.c bstree.h btree.h btree.o
	$(CC) -c $< $(CFLAGS)

stack.o:	stack.c stack.h common.h
	$(CC) -c $< $(CFLAGS)



clean:
	rm -f $(TESTS) $(OBJS)

