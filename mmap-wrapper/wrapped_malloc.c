#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"

void *__real_wmallocwmalloc(size_t id, size_t size);
void __real_wfree(size_t id, void *object);


/* 
 * __wrap_malloc - malloc wrapper function 
 */
void *__wrap_wmalloc(size_t id, size_t size)
{
    //void *ptr = malloc(size);
    void *ptr = allocate_lib(id, size);
    //printf("%ld mallocd(%ld) = %p\n", id, size, ptr);
    return ptr;
}

/* 
 * __wrap_free - free wrapper function 
 */
void __wrap_wfree(size_t id, void *object)
{
    //free(object);
    //printf("%ld free(%p)\n", id, object);
}