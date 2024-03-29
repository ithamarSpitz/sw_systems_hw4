all: graph

main.o: main.c graf.h
	gcc -Wall -g -c main.c graf.h

graph: main.o
	gcc -Wall -g -o graph main.o -lm

.PHONY: clean

clean:
	rm -f *.gch *.o graph
