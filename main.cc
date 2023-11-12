#include "tokenizer.h"

int main(int argc, char *argv[]) {
    std::string fileContent("hello world");
    Tokenizer(fileContent).tokenize();
}