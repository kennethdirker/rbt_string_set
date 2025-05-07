FLAGS=-std=c++11 -Wall -O3

.PHONY: clean test

all: main

main: main.o Set.o RedBlackTree.o
	g++ $(FLAGS) -o main main.o Set.o RedBlackTree.o

main.o: main.cpp
	g++ $(FLAGS) -o main.o -c main.cpp

Set.o: Set.h Set.cpp
	g++ $(FLAGS) -o Set.o -c Set.cpp

RedBlackTree.o: RedBlackTree.cpp RedBlackTree.h
	g++ $(FLAGS) -o RedBlackTree.o -c RedBlackTree.cpp

clean:
	rm -f *.o *.gch test main