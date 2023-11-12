#include "mod.h"

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class TraitName
int Tokenizer::traitNameLength() {
    // traits start with uppercase letters
    if(!isupper(fileContent[i]))
        return 0;

    // look while character is alphanumeric
    int j;
    for(j=i+1; j<n; j++) {
        if(!isalnum(fileContent[j]))
            break;
    }

    return j-i;
}