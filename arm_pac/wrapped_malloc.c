#include <stdio.h>
#include <stdlib.h>
#include "Documentor.h"

void *__real_wmallocwmalloc(size_t pointer, size_t size);
void __real_wfree(size_t pointer, void *object);


/* 
 * __wrap_malloc - malloc wrapper function 
 */
void *__wrap_wmalloc(size_t pointer, size_t size)
{
    void *ptr = malloc(size);
    insert_newBlock(pointer, (uintptr_t)ptr, size);
    printf("%0x mallocd(%ld) = %0x\n", (uintptr_t)pointer, size, ptr);
    return ptr;
}

/* 
 * __wrap_free - free wrapper function 
 */
void __wrap_wfree(size_t pointer, void *object)
{
    //free(object);
    free_newBlock(pointer, (uintptr_t)object);
    printf("%ld free(%p)\n", pointer, object);
}
