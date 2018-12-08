all: btree
btree: func.o main.o
	gcc -g -o btree func.o main.o
func.o: func.c func.h
	gcc -g -o func.o -c func.c -W -Wall -ansi -pedantic
main.o: main.c func.h
	gcc -g -o main.o -c main.c -W -Wall -ansi -pedantic
clean: rm -rf *.o btree

