CC=gcc
CFLAGS=-g -Wno-int-to-pointer-cast

TESTS=t_lstring t_btree t_bstree t_stack t_sort \
			t_list

OBJS=lstring.o btree.o bstree.o stack.o sort.o \
		 list.o

all: $(OBJS) $(TESTS)

test:	$(TESTS)

NETM:
	$(MAKE) -C NETM/ all


t_lstring:	t_lstring.c lstring.o
	$(CC) -o $@ $^ $(CFLAGS)

t_btree:	t_btree.c btree.o stack.o
	$(CC) -o $@ $^ $(CFLAGS)

t_bstree: t_bstree.c btree.o bstree.o stack.o
	$(CC) -o $@ $^ $(CFLAGS)
	
t_stack:	t_stack.c stack.o
	$(CC) -o $@ $^ $(CFLAGS)

t_sort:	t_sort.c sort.o
	$(CC) -o $@ $^ $(CFLAGS)

t_list:	t_list.c list.o
	$(CC) -o $@ $^ $(CFLAGS)


lstring.o: lstring.c
	$(CC) -c $^ $(CFLAGS)

btree.o: btree.c stack.o
	$(CC) -c $^ $(CFLAGS)

bstree.o: bstree.c btree.o
	$(CC) -c $^ $(CFLAGS)

stack.o:	stack.c
	$(CC) -c $^ $(CFLAGS)

sort.o:	sort.c
	$(CC) -c $^ $(CFLAGS)


list.o:	list.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(TESTS) $(OBJS)
	$(MAKE) -C NETM/ clean



