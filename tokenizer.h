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
    NUMBER_OF_ELEMENTS // should always be last enum member
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
        // the state variables of the Tokenizer
        std::string fileContent;
        int i;  // our current position
        int n;  // the length of fileContent


        // helper functions that use the state
        void advanceWhitespace(); // advances i while there is whitespace

        Token nextToken(); // advances i and returns a corresponding token

        // functions that find, for each respective token class,
        // the maximum length of a string starting at i
        // that satisfies the class
        // or 0 otherwise
        int commentLength();
        int identifierLength();
        int traitNameLength();
        int symbolLength();
        int integerLiteralLength();
        int floatingLiteralLength();
        int stringLiteralLength();
        int invalidLength();
};
#endif