#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
int Insert_newDoc();
void insert_newBlock(uint64_t my_pointer, uintptr_t pointer_addr, size_t size);
void free_newBlock(uint64_t my_pointer, uintptr_t pointer_addr);
void Insert_newBlock_withID(int id, uintptr_t pointer_addr, size_t size);
void Delete_Doc(int id);
#ifdef __cplusplus
}
#endif
