run: program
	./program

program: Source.c
	gcc -Wall -std=c11 Source.c -o program

build: program
