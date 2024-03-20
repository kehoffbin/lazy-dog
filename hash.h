#ifndef HASH_H
#define HASH_H

struct HashEntry {
    struct HashEntry *next;
    char* str;
    int value;
};

struct HashTable {
    struct HashEntry** entries;    
};

// constructs an empty hash table
struct HashTable make_hash_table();

// finds a given string
// if not found, returns -1
int find(struct HashTable *hashTable, char* str);

// inserts a string with a given value
// assumes str is not already in the table
void push_h(struct HashTable *hashTable, char* str, int i);

#endif