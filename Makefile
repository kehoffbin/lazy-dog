# link the top-level .o files
# and the module/main.o files together
lazy-dog: main.o tokenizer/main.o
	g++ main.o tokenizer/main.o -o lazy-dog

# module/mod.h is the only public information
main.o: main.cc tokenizer/mod.h
	g++ -c main.cc

# recursively make module/main.o
tokenizer/main.o: tokenizer/*
	make --no-print-directory -C tokenizer

clean:
	rm lazy-dog *.o */*.o