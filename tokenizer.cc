#include "tokenizer.h"
#include<set>
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
