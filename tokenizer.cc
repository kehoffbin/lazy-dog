#include "tokenizer.h"
Tokenizer::Tokenizer(std::string &fileContent_) {
    fileContent=fileContent_;
    i=0;
}

std::vector<Token> Tokenizer::tokenize() {
    return std::vector<Token>();
}