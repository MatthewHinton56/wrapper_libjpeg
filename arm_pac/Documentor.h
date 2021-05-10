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
uint8_t* compute_Hash(int id);
void save_hash(uint8_t* hash_result);
bool compare_hash(uint8_t* hash_result);
uint8_t saved_b1;
uint8_t saved_b2;
uint8_t saved_b3;
uint8_t saved_b4;
uint8_t saved_b5;
uint8_t saved_b6;
uint8_t saved_b7;
uint8_t saved_b8;

#ifdef __cplusplus
}
#endif
