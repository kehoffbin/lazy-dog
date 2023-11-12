#include "mod.h"

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Comment
int Tokenizer::commentLength() {
    // comments start with #
    if(fileContent[i] != '#')
        return 0;

    // explore until we find a \n
    int j;
    for(j=i+1; j<n; j++) {
        if(fileContent[j] == '\n')
            break;
    }

    // j is the first character not part of the comment
    return j-i;
}