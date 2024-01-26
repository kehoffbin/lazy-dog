cc_files=$(wildcard *.cc)
o_files=$(patsubst %.cc,%.o,$(cc_files))

# partially link all .o files together into
# main.o
# note that main.o is not in o_files, since there is no main.cc
main.o: $(o_files)
	echo $(o_files)
	@echo ld -r *.o
	@ld -r $(o_files) -o main.o
	
mod.o: mod.cc mod.h whitespace.h
	g++ -c mod.cc

comment.o: comment.cc mod.h
	g++ -c comment.cc

floating-literal.o: floating-literal.cc mod.h
	g++ -c floating-literal.cc

identifier.o: identifier.cc mod.h
	g++ -c identifier.cc

integer-literal.o: integer-literal.cc mod.h
	g++ -c integer-literal.cc

invalid.o: invalid.cc whitespace.h mod.h
	g++ -c invalid.cc

string-literal.o: string-literal.cc mod.h
	g++ -c string-literal.cc

symbol.o: symbol.cc mod.h
	g++ -c symbol.cc

trait-name.o: trait-name.cc mod.h
	g++ -c trait-name.cc

whitespace.o: whitespace.cc whitespace.h mod.h
	g++ -c whitespace.cc

