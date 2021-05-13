#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct packed_ret_struct {
    void *lib;
    void *client;
} packed_ret_t;

uint64_t create_allocator();
void *allocate_lib(uint64_t id, size_t size);
packed_ret_t allocate_client(uint64_t id, size_t size);
void *lib_to_client(uint64_t id, void* lib_ptr);
void disable_lib(uint64_t id);
void enable_lib(uint64_t id);
void delete_allocator(uint64_t id);

#ifdef __cplusplus
}
#endif
