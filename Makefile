run: program
	./program

program: Source.c
	g++ -Wall -std=c11 Source.c -o program

build: program
