#include "hash.h"

#include <string.h>
#include <stdlib.h>

const int size = 256;

// djb2 by Dan Bernstein
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

struct HashTable make_hash_table() {
    struct HashTable hashTable;
    hashTable.entries = calloc(size, sizeof(struct HashEntry*));
    return hashTable;
}

int find(struct HashTable *hashTable, char* str) {
    int d = (int) hash(str) % size;
    struct HashEntry *hashEntry = hashTable->entries[d];
    while(hashEntry) {
        // if both strings are the same, we found it
        if(strcmp(hashEntry->str, str) == 0)
            return hashEntry->value;
        hashEntry = hashEntry->next;
    }
    return -1;
}

void push_h(struct HashTable *hashTable, char* str, int i) {
    int d = (int) hash(str) % size;
    struct HashEntry *hashEntry = malloc(sizeof(hashEntry));
    hashEntry->next = hashTable->entries[d];
    hashTable->entries[d] = hashEntry;
    hashEntry->str = str;
    hashEntry->value = i; 

}
