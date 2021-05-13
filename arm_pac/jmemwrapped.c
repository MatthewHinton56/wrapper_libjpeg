#include <stdio.h>
#include "jmemwrapped.h"

void __attribute__ ((noinline)) *wmalloc(size_t id, size_t size) {
    printf("Here %ld %ld\n", id, size);
    for (int i = 0; i < 1000; i++) {
        printf("");
    }
    return NULL;
}

void __attribute__ ((noinline)) *wfree(size_t id, void *object) {
    printf("also here %ld %p\n", id, object);
    for (int i = 0; i < 1000; i++) {
        printf("");
    }
}