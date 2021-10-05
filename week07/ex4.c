#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// There is no clean way to do it without passing
// previous size of the container, since realloc
// itself makes special calls to the heap in order
// to determine (approximate) size of the array
void *my_realloc(void* ptr, int prev_size, int new_size) {
    if (ptr == NULL) {
        return malloc(new_size);
    }
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    void *new_mem = malloc(new_size);
    if (prev_size > new_size) {
        memcpy(new_mem, ptr, new_size);
    } else {
        memcpy(new_mem, ptr, prev_size);
    }
    return new_mem;
}
