compile:
	g++ -Wall -std=c++14 -g -c -O0 -pedantic-errors QueType.cpp QueType.h TreeType.h TreeType.cpp TreeDr.cpp
	g++ QueType.o TreeType.o TreeDr.o -o TreeDr

run:
	./TreeDr

clean:
	rm ./TreeDr
