#include "mod.h"
#include "whitespace.h"
// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Invalid
int Tokenizer::invalidLength() {
    // take anything until we get whitespace
    int j;
    for(j=i; j<n; j++) {
        if(isWhitespace(fileContent[j]))
            break;
    }
    return j-i;
}