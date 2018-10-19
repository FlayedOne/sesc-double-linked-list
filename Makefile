run: program
	./program

program: Source.c
	g++ -Wall Source.cpp -o program

build: program
