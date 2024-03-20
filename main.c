#include "hash.h"
#include <stdio.h>

int main() {
    struct HashTable hashTable = make_hash_table();
    push_h(&hashTable, "Hallo", 3);
    push_h(&hashTable, "Welt", 6);
    printf("%d", find(&hashTable, "Hallo"));
}