.PHONY = all clean run practica03
SHELL = /bin/bash
CC = gcc
CFLAGS = -g

all: practica03 run

run: practica03
	./practica03.o

practica03: practica03.c
	${CC} ${CFLAGS} practica03.c -o practica03.o

clean:
	rm -f practica03.o
