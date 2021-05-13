#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
//#include <//assert.h>
#include <stdbool.h>

#define ALIGNMENT 4096 /* The alignment of all payloads returned by umalloc */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

typedef struct mem_region_struct{
    uintptr_t lib;
    uintptr_t client;
    size_t size;
    uint64_t region_id;
    int fd;
    struct mem_region_struct *next;
} mem_region_t;

typedef struct mem_block_struct{
    uintptr_t lib;
    uintptr_t client;
    size_t size;
    bool allocated;
    uint64_t region_id;
    struct mem_block_struct *next;
} mem_block_t;

typedef struct allocator_struct {
    mem_region_t *regions;
    mem_block_t *blocks;
    uint64_t next_region_id;
    uint64_t id;
    bool enabled;
    struct allocator_struct *next;
} allocator_t;

mem_block_t *create_memory_region(allocator_t *allocator, size_t size) {
    char file_template[] = "regionsXXXXXX";
    int fd =  mkstemp(file_template);
    unlink(file_template);
    if (fd == -1)
        fprintf(stderr, "Error creating file: %s\n", strerror( errno ));
    ftruncate(fd, size);
    void *lib_addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    void *client_addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (!allocator->enabled) {
        mprotect((void*)lib_addr, size, PROT_NONE);
    }

    mem_region_t *new_region = (mem_region_t *)malloc(sizeof(mem_region_t));
    //printf("loc: %p region: %p\n", new_region, lib_addr);

    if (allocator->regions == NULL) {
        allocator->regions = new_region;
    } else {
        mem_region_t *region = allocator->regions;
        while(region->next != NULL) {
            region = region->next;
        }
        region->next = new_region;
    }

    new_region->lib = (uintptr_t)lib_addr;
    new_region->client = (uintptr_t)client_addr;
    new_region->size = size;
    new_region->fd = fd;
    new_region->region_id = ++allocator->next_region_id;
    new_region->next = NULL;

    mem_block_t *new_block = (mem_block_t*)malloc(sizeof(mem_block_t));
    new_block->lib = (uintptr_t)lib_addr;
    new_block->client = (uintptr_t)client_addr;
    new_block->size = size;
    new_block->allocated = false;
    new_block->region_id = allocator->next_region_id;
    new_block->next = NULL;

    if (allocator->blocks == NULL) {
        allocator->blocks = new_block;
    } else {
        mem_block_t *block = allocator->blocks;
        while(block->next != NULL) {
            block = block->next;
        }
        block->next = new_block;
    }

    return new_block;
}

mem_block_t *find_block(allocator_t *allocator, size_t size) {
    mem_block_t *block = allocator->blocks;
    while(block != NULL) {
        //printf("block: %p\n", block);
        if (block->size >= size && !block->allocated) {
            return block;
        }
        block = block->next;
    }
    return NULL;
}

packed_ret_t allocate(allocator_t *allocator, size_t size) {
    //printf("allocate: %d\n", size);
    mem_block_t *block = find_block(allocator, size);
    if (block == NULL) {
        //printf("new block allocate: %d\n", size);
        block = create_memory_region(allocator, ALIGN(size));
    }

    uintptr_t free_lib_addr_ptr = block->lib + size;
    uintptr_t free_client_addr_ptr = block->client + size;

    
    mem_block_t *free_block = (mem_block_t *)malloc(sizeof(mem_block_t));
    free_block->lib = free_lib_addr_ptr;
    free_block->client = free_client_addr_ptr;
    free_block->size = block->size - size;
    free_block->allocated = false;
    free_block->region_id = block->region_id;
    free_block->next = NULL;

    block->size = size;
    free_block->next = block->next;
    block->next = free_block;
    block->allocated = true;
    //printf("fb next %p\n", block->next);
    //printf("fb next %p\n", free_block->next);


    //printf("Allocated address: %p allocated length %ld\n", block->lib, size);

    packed_ret_t ret;
    ret.client = (void*)block->client;
    ret.lib = (void*)block->lib;
    return ret;
}

bool holds_address(allocator_t *allocator, uintptr_t lookup_addr) {
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        //printf("(%p %p)\n", (void*)region->lib, (void*)(region->lib + region->size));
        if (region->lib <= lookup_addr && (region->lib + region->size) > lookup_addr)
            return true;
        region = region->next;
    }

    return false;
}

void deactivate_regions(allocator_t *allocator) {
    allocator->enabled = false;
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        mprotect((void*)region->lib, region->size, PROT_NONE);
        region = region->next;
    }
}

void activate_regions(allocator_t *allocator) {
    allocator->enabled = true;
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        mprotect((void*)region->lib, region->size, PROT_READ | PROT_WRITE);
        region = region->next;
    }
}

void unmap_regions(allocator_t *allocator) {
    mem_region_t *region = allocator->regions;
   // size_t num_regions = 0;
    while(region != NULL) {
        munmap((void*)region->lib, region->size);
        munmap((void*)region->client, region->size);
        close(region->fd);
        mem_region_t *temp = region;
        region = region->next;
        free(temp);
        //num_regions++;
    }
    //printf("num regions: %d\n", num_regions);
}

void free_blocks(allocator_t *allocator) {
    mem_block_t *block = allocator->blocks;
    //size_t num_blocks = 0;
    while(block != NULL) {
        mem_block_t *temp = block;
        block = block->next;
        free(temp);
        //num_blocks++;
    }
    //printf("num blocks: %d\n", num_blocks);
}

uint64_t next_allocator = 0;
allocator_t *allocators = NULL;

uint64_t create_allocator() {
    uint64_t id = ++next_allocator;
    
    allocator_t *new_allocator = (allocator_t *)malloc(sizeof(allocator_t));
    new_allocator->enabled = false;
    new_allocator->id = id;
    if (allocators == NULL) {
        allocators = new_allocator;
    } else {
        allocators->next = new_allocator;
    }
    new_allocator->next = NULL;
    new_allocator->regions = NULL;
    new_allocator->blocks = NULL;
    

    return id;
}

packed_ret_t allocate_client(uint64_t id, size_t size) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    return allocate(allocator, size);
}

void *allocate_lib(uint64_t id, size_t size) {

    uintptr_t lookup_addr = id;

    allocator_t *allocator = allocators;
    while(allocator != NULL) {
        if (holds_address(allocator, lookup_addr)) {
            break;
        }
        allocator = allocator->next;
    }

    return allocate(allocator, size).lib;
}

#define PAGESIZE 4096

void *lib_to_client(uint64_t id, void* lib_ptr) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    mem_region_t *region = allocator->regions;

    while(region != NULL) {

        uintptr_t lib_ptr_working = (uintptr_t)lib_ptr;
        uintptr_t lib_ptr_page = lib_ptr_working - (lib_ptr_working % region->size);
        uintptr_t lib_ptr_offset = ((uintptr_t)lib_ptr)  % region->size;

        if (region->lib == lib_ptr_page) {
            return (void*) (region->client + lib_ptr_offset);
        }
        region = region->next;
    }
    return NULL;
}

void disable_lib(uint64_t id) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    deactivate_regions(allocator);
}

void enable_lib(uint64_t id) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    activate_regions(allocator);
}

void delete_allocator(uint64_t id) {
    allocator_t *allocator = allocators;
    allocator_t *prev = allocators;
    while(allocator != NULL && allocator->id != id) {
        prev = allocator;
        allocator = allocator->next;
    }

    unmap_regions(allocator);
    free_blocks(allocator);
    allocator->blocks = NULL;
    allocator->regions = NULL;

    if (prev == allocator) {
        allocators = allocators->next;
    } else {
        prev->next = allocator->next;
    }
    free(allocator);
}