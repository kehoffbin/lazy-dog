/* a primitive Vector implementation */

#ifndef VEC_H
#define VEC_H

struct Vec {
    int capacity;
    int size;
    void** data;
};

// creates an empty vec
struct Vec make_vec();

// appends element to the vector
// returns the index of the element
int push(struct Vec *vec, void* value);

// gets the ith element
void* get(struct Vec *vec, int i);

#endif