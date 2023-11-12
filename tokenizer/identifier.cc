#include "mod.h"

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Identifier
int Tokenizer::identifierLength() {
    // identifiers start with a lowercase letter
    if(!islower(fileContent[i]))
        return 0;

    // the length of the longest valid token
    int validLength = 1;

    // the last character is fileContent[i]
    // and therefore a lowercase letter
    // not a dash
    bool lastCharacterWasDash = false;

    // explore remainder of fileContent
    // starting at i+1 because i was already checked
    for(int j=i+1; j<n; j++) {
        // check for illegal characters
        char c = fileContent[j];
        if(!(islower(c) || isdigit(c) || c=='-'))
            break;
        
        // check if current character is dash
        if(c == '-') {
            // if the last character was also a dash
            // we can stop our search and give back
            // the best we got
            if(lastCharacterWasDash)
                break;

            // lets remember that this was dash
            lastCharacterWasDash = true;

            // otherwise  a longer length might be valid
            continue;
        }

        // this character is not a dash
        lastCharacterWasDash=false;

        // we dont end in a dash, so this length is valid
        // remember that i+validLength is the first invalid position
        validLength = j + 1 - i;
    }

    return validLength;

}