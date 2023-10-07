.PHONY = all clean run

SHELL = /bin/bash

CC = gcc

CFLAGS = -g

all: 03 run

run: 03
	./03

03: 03.c
	${CC} ${CFLAGS} 03.c -o 03

clean:
	rm -f 03.o
