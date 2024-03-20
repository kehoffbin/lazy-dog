// a primitive Vector implementation
struct Vec {
    int capacity;
    int size;
    void** data;
};

// creates an empty vec
struct Vec make_vec();

// appends element to the vector
void push(struct Vec *vec, void* value);

// gets the ith element
void* get(struct Vec *vec, int i);