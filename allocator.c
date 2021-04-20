#include "allocator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
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

typedef struct lookup_struct {
    uintptr_t lib;
    uintptr_t client;
    struct lookup_struct *next;
} lookup_t;

typedef struct allocator_struct {
    mem_region_t *regions;
    mem_block_t *blocks;
    lookup_t *lookups;
    uint64_t next_region_id;
    uint64_t id;
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

    mem_region_t *new_region = (mem_region_t *)malloc(sizeof(mem_region_t));

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

    mem_block_t *new_block = (mem_block_t*)malloc(sizeof(mem_block_t));
    new_block->lib = (uintptr_t)lib_addr;
    new_block->client = (uintptr_t)client_addr;
    new_block->size = size;
    new_block->allocated = false;
    new_block->region_id = allocator->next_region_id;

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
        if (block->size >= size && !block->allocated) {
            return block;
        }
        block = block->next;
    }
    return NULL;
}

packed_ret_t allocate(allocator_t *allocator, size_t size) {
    mem_block_t *block = find_block(allocator, size);
    if (block == NULL) {
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

    block->size = size;
    free_block->next = block->next;
    block->next = free_block;
    block->allocated = true;
    
    uintptr_t lib_addr_ptr = block->lib;
    uintptr_t client_addr_ptr = block->client;

    lookup_t *new_lookup = (lookup_t *)malloc(sizeof(lookup_t));
    new_lookup->client = client_addr_ptr;
    new_lookup->lib = lib_addr_ptr;
    new_lookup-> next = allocator->lookups;
    allocator->lookups = new_lookup;

    printf("Allocated address: %p allocated length %ld\n", block->lib, size);

    packed_ret_t ret;
    ret.client = (void*)block->client;
    ret.lib = (void*)block->lib;
    return ret;
}

bool holds_address(allocator_t *allocator, uintptr_t lookup_addr) {
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        printf("(%p %p)\n", (void*)region->lib, (void*)(region->lib + region->size));
        if (region->lib <= lookup_addr && (region->lib + region->size) > lookup_addr)
            return true;
        region = region->next;
    }

    return false;
}

void deactivate_regions(allocator_t *allocator) {
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        mprotect((void*)region->lib, region->size, PROT_NONE);
        region = region->next;
    }
}

void activate_regions(allocator_t *allocator) {
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        mprotect((void*)region->lib, region->size, PROT_READ | PROT_WRITE);
        region = region->next;
    }
}

void unmap_regions(allocator_t *allocator) {
    mem_region_t *region = allocator->regions;
    while(region != NULL) {
        munmap((void*)region->lib, region->size);
        close(region->fd);
        region = region->next;
    }
}

uint64_t next_allocator = 0;
allocator_t *allocators;

uint64_t create_allocator() {
    uint64_t id = ++next_allocator;
    
    allocator_t *new_allocator = (allocator_t *)malloc(sizeof(allocator_t));
    new_allocator->id = id;
    if (allocators == NULL) {
        allocators = new_allocator;
    } else {
        allocators->next = new_allocator;
    }

    return id;
}

packed_ret_t allocate_client(uint64_t id, size_t size) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    assert(allocator != NULL);

    return allocate(allocator, size);
}

void *allocate_lib(uint64_t id, size_t size) {

    uintptr_t lookup_addr = id;
    printf("scan %p\n", (void*)lookup_addr);

    allocator_t *allocator = allocators;
    while(allocator != NULL) {
        if (holds_address(allocator, lookup_addr)) {
            break;
        }
        allocator = allocator->next;
    }

    assert(allocator != NULL);
    return allocate(allocator, size).lib;
}

#define PAGESIZE 4096

void *lib_to_client(uint64_t id, void* lib_ptr) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    assert(allocator != NULL);
    mem_region_t *region = allocator->regions;

    uintptr_t lib_ptr_working = (uintptr_t)lib_ptr;
    uintptr_t lib_ptr_page = lib_ptr_working - (lib_ptr_working % PAGESIZE);
    uintptr_t lib_ptr_offset = ((uintptr_t)lib_ptr) % PAGESIZE;
    printf("comp: %p %p\n", (void*)lib_ptr_page, (void*)lib_ptr_offset);

    while(region != NULL) {
        printf("%p =? %p %p\n", lib_ptr, (void*)region->lib, (void*)region->client);
        if (region->lib == lib_ptr_page) {
            printf("found %p\n", (void*) (region->client + lib_ptr_offset));
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
    assert(allocator != NULL);
    deactivate_regions(allocator);
}

void enable_lib(uint64_t id) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    assert(allocator != NULL);
    activate_regions(allocator);
}

void delete_allocator(uint64_t id) {
    allocator_t *allocator = allocators;
    while(allocator != NULL && allocator->id != id)
        allocator = allocator->next;
    assert(allocator != NULL);
    unmap_regions(allocator);
}