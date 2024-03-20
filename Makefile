lazy-dog: main.o vec.o
	gcc main.o vec.o -o lazy-dog

main.o: main.c vec.h
	gcc -c main.c

vec.o: vec.c vec.h
	gcc -c vec.c