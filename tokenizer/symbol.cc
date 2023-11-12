#include "mod.h"
#include<set>
const std::string symbolChars = "!$%&()*+,-./:;<=>?[]\\_{}|~"; 
const std::vector<std::string> elementarySymbols = {
    "&", "&!", "&?", "(", ")", ",", "->", ".", "..", "...",
    ":", "::", "=", "=>", ">", "[", "]", "_", "__", "{", "}", "|"
};
const std::set<std::string> elementarySymbolsSet 
    (elementarySymbols.begin(), elementarySymbols.end());


// the maximum length of any elementary symbol
const int maxLengthElementarySymbol = 3;

// finds the longest length of a prefix of s that is an elementary symbol
int elementaryPrefix(std::string s) {
    // only check the first maxLengthElementarySymbol,...,2,1
    // characters
    int startLength = std::min((int)s.size(),maxLengthElementarySymbol);
    for(int l=startLength; l>0; l--) {
        if(elementarySymbolsSet.count(s.substr(0,l)) != 0) 
            return l;
        
    }
    return 0;
}

// figures out the maximum length of a substring of fileContent
// starting at i
// that is of type class Symbol
int Tokenizer::symbolLength() {
    // look for symbol characters
    int j;
    for(j=i; j<n; j++) {
        // breaks if symbolChars does not contain fileContent[j]
        if(symbolChars.find(fileContent[j]) == std::string::npos)
            break;
    }
    if(i==j)
        return 0;

    // now figure out whether the symbol 
    // can be broken down into elementary symbols
    bool breakable=true;
    for(int k=i; k<j;) {
        // a trailing dash is considered elementary
        // this prevents 1,-1 to be read as 1 ,- 1 instead of 1, -1
        if(k==j-1 && i<j-1 && fileContent[k]=='-') {
            breakable=true;
            break;
        }

        int prefixLength = elementaryPrefix(fileContent.substr(k, j-k));
        if(prefixLength == 0) {
            breakable=false; // no more elementary symbol
            break;
        }

        // break off the prefix, check the remainder
        k += prefixLength;
    }

    // if the symbol is breakable, only return the first part
    if(breakable)
        return elementaryPrefix(fileContent.substr(i,j-i));
    
    // otherwise, return the first symbol
    return j-i;
}