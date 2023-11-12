#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>

enum TokenClass {
    Comment,
    Identifier,
    TraitName,
    Symbol,
    IntegerLiteral,
    FloatingLiteral,
    StringLiteral,
    Invalid,
    NUMBER_OF_TOKEN_CLASSES // should always be last enum member
};

struct Token {
    int start;
    int length;
    std::string content;
    TokenClass tokenClass;
};

// temporary object responsible for turning
// a file content string into a vector of tokens
class Tokenizer {
    public:
        Tokenizer(std::string &fileContent);
        std::vector<Token> tokenize();
    private:
        std::string fileContent;
        int i;
};
#endif