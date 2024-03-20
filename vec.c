#include "vec.h"
#include<stdlib.h>

struct Vec make_vec() {
    struct Vec vec;
    vec.capacity = 8;
    vec.size = 0;
    vec.data = malloc(vec.capacity * sizeof(void*));
    return vec;
}

int push(struct Vec *vec, void* value) {
    if(vec->size > vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(void*));
    }

    int i = vec->size;
    vec->data[i] = value;
    vec->size += 1;
    return i;
    
}

void* get(struct Vec *vec, int i) {
    return vec->data[i];
}