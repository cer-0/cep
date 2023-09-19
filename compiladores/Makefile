.PHONY = all clean run test

SHELL = /bin/bash

CC = gcc

CFLAGS = -g

all: identificador test

test: identificador
	./identificador_tokens.out 1
	./identificador_tokens.out 9991
	./identificador_tokens.out -1
	./identificador_tokens.out +1.0
	./identificador_tokens.out +1.0e-10
	./identificador_tokens.out +7331.1234E+10
	./identificador_tokens.out +7331.1234e+10
	./identificador_tokens.out +7331.1234e-10
	./identificador_tokens.out r2d2
	./identificador_tokens.out @rmando
	./identificador_tokens.out gonzál3z
	./identificador_tokens.out +
	./identificador_tokens.out \*
	./identificador_tokens.out \/
	./identificador_tokens.out \<
	./identificador_tokens.out \>=
	./identificador_tokens.out \!=
	./identificador_tokens.out \!
	./identificador_tokens.out \|\|
	./identificador_tokens.out \&

# run: identificador
# 	./identificador_tokens.out

identificador: 02_identificador_tokens.c
	${CC} ${CFLAGS} 02_identificador_tokens.c -o identificador_tokens.out

clean:
	rm -f identificador_tokens.out
