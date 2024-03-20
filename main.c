#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct Vec vec = make_vec();
    for(size_t i = 0; i <= 100; i++) {
        push(&vec, (void*) (i*i));
    }

    free(vec.data);
}