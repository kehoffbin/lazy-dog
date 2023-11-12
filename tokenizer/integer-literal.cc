#include "mod.h"

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class IntegerLiteral
int Tokenizer::integerLiteralLength() {
    int j=i;
    // a dash in the beginning is allowed
    if(fileContent[j]=='-')
        j++;
    
    // the next symbol must be a digit
    if(!isdigit(fileContent[j]))
        return 0;
    
    // look for digits
    for(;j<n; j++) {
        if(!isdigit(fileContent[j]))
            break;
    }

    // an integer literal must not be followed by an e or a dot
    if(j<n && (fileContent[j]=='e' || fileContent[j]=='.'))
        return 0;

    return j-i;
}