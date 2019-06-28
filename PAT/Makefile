CFLAGS=-g -Wall -lm
src=$(wildcard *.c)
target=$(patsubst %.c, %, ${src})
CC=gcc

.PHONY:all clean


%.o:	%.c
	$(CC) ${CFLAGS} -c -o $@

%:	%.o
	$(CC) ${LDFLAGS} -o $@

all:	${target} 

clean: 
	rm -f ${target}
