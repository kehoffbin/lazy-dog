#include "tokenizer.h"
#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> tokenClassNames = {
    "Com", "Id ", "Tr ", "Sym", "Int", "Fl ", "Str", "Inv"
};

int main(int argc, char *argv[]) {
    std::string fileContent("123\"str\\\"ing\"::hello");
    std::vector<Token> tokens = Tokenizer(fileContent).tokenize();

    for (Token token:tokens) {
        std::cout << tokenClassNames[(int)token.tokenClass];
        std::cout << ": ";
        std::cout << token.content;
        std::cout << std::endl;
    }

}