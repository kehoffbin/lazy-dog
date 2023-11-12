#include "mod.h"
// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class StringLiteral
int Tokenizer::stringLiteralLength() {
    // we need to start with a "
    if(fileContent[i] != '\"')
        return 0;
    
    // now look for the matching "
    int j;
    for(j=i+1; j<n; j++) {
        if(fileContent[j] == '\"') {
            // check if it was escaped by backslash
            if(fileContent[j-1] == '\\')
                continue;
            else
                break;
        }
    }

    // invalid if eof was reached
    if(j==n) return 0;
    return j+1-i;
}