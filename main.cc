#include "tokenizer.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


std::vector<std::string> tokenClassNames = {
    "Com", "Id ", "Tr ", "Sym", "Int", "Fl ", "Str", "Inv"
};

int main(int argc, char *argv[]) {
    std::string fileContent;
    std::ifstream fin("test.txt");
    while(!fin.eof()) {
        std::string line;
        getline(fin, line);
        fileContent += line + "\n";
    }
    fin.close();

    std::vector<Token> tokens = Tokenizer(fileContent).tokenize();

    for (Token token:tokens) {
        std::cout << tokenClassNames[(int)token.tokenClass];
        std::cout << ": ";
        std::cout << token.content;
        std::cout << std::endl;
    }

}