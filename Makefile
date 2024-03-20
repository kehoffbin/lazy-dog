lazy-dog: main.o vec.o hash.o
	gcc main.o vec.o hash.o -o lazy-dog

main.o: main.c hash.h vec.h
	gcc -c main.c

hash.o: hash.c hash.h vec.h 
	gcc -c hash.c

vec.o: vec.c vec.h
	gcc -c vec.c

clean:
	rm *.o lazy-dog