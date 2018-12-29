CC=gcc
CFLAGS=-g -Wno-int-to-pointer-cast 
CTESTFLAGS=-Wno-int-conversion -Wno-pointer-to-int-cast

TESTS=t_lstring t_btree t_bstree t_stack t_sort \
			t_list t_queue

OBJS=lstring.o btree.o bstree.o stack.o sort.o \
		 list.o queue.o

all: $(OBJS) $(TESTS)

test:	$(TESTS)

NETM:
	$(MAKE) -C NETM/ all


t_lstring:	t_lstring.c lstring.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)

t_btree:	t_btree.c btree.o stack.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)

t_bstree: t_bstree.c btree.o bstree.o stack.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)
	
t_stack:	t_stack.c stack.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)

t_sort:	t_sort.c sort.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)

t_list:	t_list.c list.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)

t_queue:	t_queue.c queue.o
	$(CC) -o $@ $^ $(CFLAGS) $(CTESTFLAGS)



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

queue.o:	queue.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(TESTS) $(OBJS)
	rm -f *.gch
	$(MAKE) -C NETM/ clean



