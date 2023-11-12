lazy-dog: main.o tokenizer/main.o
	g++ main.o tokenizer/main.o -o lazy-dog

main.o: main.cc tokenizer/mod.h
	g++ -c main.cc

tokenizer/main.o: tokenizer/*
	make --no-print-directory -C tokenizer

clean:
	rm lazy-dog *.o */*.o