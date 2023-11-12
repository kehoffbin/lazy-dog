lazy-dog: main.o tokenizer.o
	g++ main.o tokenizer.o -o lazy-dog

main.o: main.cc tokenizer.h
	g++ -c main.cc

tokenizer.o: tokenizer.cc tokenizer.h
	g++ -c tokenizer.cc

clean:
	rm lazy-dog *.o