all: btree
btree: func.o main.o
	gcc -o btree func.o main.o
func.o: func.c
	gcc -o func.o -c func.c -W -Wall -ansi -pedantic
main.o: main.c func.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
clean: rm -rf *.o btree

