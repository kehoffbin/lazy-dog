#include "mod.h"
#include "whitespace.h"
// checks whether a character is whitespace
// as defined by lazy-dog
// that is: space, newline or tab
bool isWhitespace(char c) {
    return c == ' ' || c == '\n' || c == '\t';
}

// advances i until there is no more whitespace
void Tokenizer::advanceWhitespace() {
    while(i<n && isWhitespace(fileContent[i])) 
        i++;
}