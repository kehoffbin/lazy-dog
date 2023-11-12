#include "mod.h"
#include "whitespace.h"

Tokenizer::Tokenizer(std::string &fileContent_) {
    fileContent=fileContent_;
    i=0;
    n=fileContent.size();
}


std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    advanceWhitespace();
    while(i<n) {
        tokens.push_back(nextToken());
        advanceWhitespace();
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
    // except Invalid
    int maxLength = 0;
    TokenClass bestTokenClass;
    for(int j=0; j<lengths.size()-1; j++) {
        if(lengths[j]>maxLength) {
            maxLength = lengths[j];
            bestTokenClass = (TokenClass) j;
        }
    }

    // if all else is 0, return an invalid token
    if(maxLength == 0) {
        bestTokenClass = TokenClass::Invalid;
        maxLength = lengths[TokenClass::Invalid];
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


















