run: program
	./program

program: Source.c
	g++ -Wall -std=c11 Source.cpp -o program

build: program
