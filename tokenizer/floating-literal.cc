#include "mod.h"

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class FloatingLiteral
int Tokenizer::floatingLiteralLength() {
    // whether we 
    bool foundDot = false;
    bool foundE = false;
    
    bool foundDigit = false;
    bool foundDigitAfterDot = false;
    bool foundDigitAfterE = false;
    int j;
    for(j=i; j<n; j++) {
        char c = fileContent[j];
        if(c == '.') {
            if((!foundDigit) // a dot before any digit
                || foundE // or a dot after e
                || foundDot) // or two dots 
                return 0; // are illegal
            foundDot = true;
            continue;
        }

        if(c == 'e') {
            if((!foundDigit) // an e before any digit
                // or an e after dot without digit
                || (foundDot && !foundDigitAfterDot)
                || foundE) // or two e's
                return 0; // are illegal
            foundE = true;
            continue;
        }

        if(c == '-') {
            // a dash is only legal
            if((!foundDigit) // at the start
                || (foundE && !foundDigitAfterE)) // or right after e
                continue;
            else break;
        }

        // a non-digt character thats not dot, e or dash
        // means we reached the end of the token
        if(!isdigit(c))
            break;
        
        // report the finding of a digit
        foundDigit = true;
        if(foundDot) foundDigitAfterDot = true;
        if(foundE) foundDigitAfterE = true;
    }

    // check if either dot or e were found with a digit afterwards
    if(foundDigitAfterDot || foundDigitAfterE)
        return j-i;
    else return 0;
}