#include "tokenizer.h"
Tokenizer::Tokenizer(std::string &fileContent_) {
    fileContent=fileContent_;
    i=0;
    n=fileContent.size();
}


std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while(i<n) {
        tokens.push_back(nextToken());
    }
    return tokens;
}

// advances i and returns a corresponding token
Token Tokenizer::nextToken() {
    // for each token class,
    // figure out the maximum length 
    // of a valid token of that class
    std::vector<int> lengths(TokenClass::NUMBER_OF_ELEMENTS);
    lengths[TokenClass::Comment] = commentLength();
    lengths[TokenClass::Identifier] = identifierLength();
    lengths[TokenClass::TraitName] = traitNameLength();
    lengths[TokenClass::Symbol] = symbolLength();
    lengths[TokenClass::IntegerLiteral] = integerLiteralLength();
    lengths[TokenClass::FloatingLiteral] = floatingLiteralLength();
    lengths[TokenClass::StringLiteral] = stringLiteralLength();
    lengths[TokenClass::Invalid] = invalidLength();

    // figure out which token class allows for the longest token
    int maxLength = 0;
    TokenClass bestTokenClass;
    for(int j=0; j<lengths.size(); j++) {
        if(lengths[j]>maxLength) {
            maxLength = lengths[j];
            bestTokenClass = (TokenClass) j;
        }
    }

    // create the corresponding token
    Token token;
    token.tokenClass = bestTokenClass;
    token.start = i;
    token.length = maxLength;
    token.content = fileContent.substr(token.start, token.length);

    // advance the tokenizer
    i += token.length;

    return token;
    
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Comment
int Tokenizer::commentLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Identifier
int Tokenizer::identifierLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class TraitName
int Tokenizer::traitNameLength() {
    return 2;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Symbol
int Tokenizer::symbolLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class IntegerLiteral
int Tokenizer::integerLiteralLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class FloatingLiteral
int Tokenizer::floatingLiteralLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class StringLiteral
int Tokenizer::stringLiteralLength() {
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Invalid
int Tokenizer::invalidLength() {
    return 0;
}
