#include "Documentor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unordered_map>
#include "sha1_arm.h"
using namespace std;
int curr_id = 0;
unordered_map<int, unordered_map<uintptr_t, size_t>> my_Documentation; 
saved_b1 = 0;
saved_b2 = 0;
saved_b3 = 0;
saved_b4 = 0;
saved_b5 = 0;
saved_b6 = 0;
saved_b7 = 0;
saved_b8 = 0;


int Insert_newDoc() {
    int id=curr_id;
    unordered_map<uintptr_t, size_t> curr_map;
    my_Documentation[id] = curr_map;
    curr_id = curr_id+1;
    return id;
}

void Delete_Doc(int id) {
    my_Documentation.erase(id);
}

void Insert_newBlock_withID(int id, uintptr_t pointer_addr, size_t size) {
    my_Documentation[id][pointer_addr] = size;
}
//return the id that holds this lookupaddr
uint64_t holds_address(uintptr_t lookup_addr) {
    for (auto it_doc : my_Documentation){
        //printf("my id is: %d\n", it_doc.first);
        for (auto it_map : it_doc.second){
            //printf("it_map %0x, %ld\n", it_map.first, it_map.second);
            if (it_map.first <= lookup_addr && (it_map.first + it_map.second) > lookup_addr){
                return it_doc.first;
            }
        }    
    }
    return -1;
}

void insert_newBlock(uint64_t my_pointer, uintptr_t pointer_addr, size_t size){
    printf("insert_newBlock %0x, %0x, %ld\n", my_pointer,pointer_addr, size);
    int find_id = holds_address((uintptr_t)my_pointer);
    printf("%d\n", find_id);
    my_Documentation[find_id][pointer_addr] = size;
}

void free_newBlock(uint64_t my_pointer, uintptr_t pointer_addr){
    printf("free_newBlock %ld, %0x\n", my_pointer,pointer_addr);
    int find_id = holds_address(my_pointer);
    printf("%d\n", find_id);
    my_Documentation[find_id].erase(pointer_addr); 
}

uint8_t* compute_Hash(int id){
    uint8_t hash_result[8];

    int number_Block = my_Documentation[id].size();
    unordered_map<uintptr_t, size_t> my_map = my_Documentation[id]
    uint8_t* hash_sum = (uint8_t*)malloc(8*number_Block * sizeof(uint8_t));
    
    int index = 0;
    for (auto it : my_map){
        uint8_t* vars = (uint8_t *) (it.first);

        uint32_t state[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
        sha1_process_arm(state, (const uint8_t*)it.first, it.second);

        uint8_t b1 = (uint8_t)(state[0] >> 24);
        uint8_t b2 = (uint8_t)(state[0] >> 16);
        uint8_t b3 = (uint8_t)(state[0] >>  8);
        uint8_t b4 = (uint8_t)(state[0] >>  0);
        uint8_t b5 = (uint8_t)(state[1] >> 24);
        uint8_t b6 = (uint8_t)(state[1] >> 16);
        uint8_t b7 = (uint8_t)(state[1] >>  8);
        uint8_t b8 = (uint8_t)(state[1] >>  0);
        hash_sum[index]=b1;
        index = index+1;
        hash_sum[index]=b2;
        index=index+1;
        hash_sum[index]=b3;
        index=index+1;
        hash_sum[index]=b4;
        index = index+1;
        hash_sum[index]=b5;
        index = index+1;
        hash_sum[index]=b6;
        index = index+1;
        hash_sum[index]=b7;
        index = index+1;
        hash_sum[index]=b8;
        index = index+1;
																	 
     }
     uint32_t state[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
     sha1_process_arm(state, hash_sum, 8*my_map.size());
     const uint8_t b1 = (uint8_t)(state[0] >> 24);
     const uint8_t b2 = (uint8_t)(state[0] >> 16);
     const uint8_t b3 = (uint8_t)(state[0] >>  8);
     const uint8_t b4 = (uint8_t)(state[0] >>  0);
     const uint8_t b5 = (uint8_t)(state[1] >> 24);
     const uint8_t b6 = (uint8_t)(state[1] >> 16);
     const uint8_t b7 = (uint8_t)(state[1] >>  8);
     const uint8_t b8 = (uint8_t)(state[1] >>  0);

     printf("SHA1 hash of empty message: ");
     printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",b1, b2, b3, b4, b5, b6, b7, b8);
     hash_result[0] = b1;
     hash_result[1] = b2;
     hash_result[2] = b3;
     hash_result[3] = b4;
     hash_result[4] = b5;
     hash_result[5] = b6; 
     hash_result[6] = b7;
     hash_result[7] = b8;                             
     return hash_result;
}

void save_hash(uint8_t* hash_result){
    saved_b1 = hash_result[0];
    saved_b2 = hash_result[1];
    saved_b3 = hash_result[2];
    saved_b4 = hash_result[3];    
    saved_b5 = hash_result[4];    
    saved_b6 = hash_result[5];    
    saved_b7 = hash_result[6];    
    saved_b8 = hash_result[7];
    printf("saving SHA1 hash of empty message: ");
    printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",hash_result[0], hash_result[1], hash_result[2], hash_result[3], hash_result[4], hash_result[5], hash_result[6], hash_result[7]);
         
}

bool compare_hash(uint8_t* hash_result){
    printf("saved SHA1 hash of empty message: ");
    printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",saved_b1, saved_b2, saved_b3, saved_b4, saved_b5, saved_b6, saved_b7, saved_b8);
    
    printf("compared newly computed SHA1 hash of empty message: ");
    printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",hash_result[0], hash_result[1], hash_result[2], hash_result[3], hash_result[4], hash_result[5], hash_result[6], hash_result[7]);
     
    bool same = (saved_b1 == hash_result[0])&&(saved_b2 == hash_result[1])&&(saved_b3 == hash_result[2])&&(saved_b4 == hash_result[3])&&(saved_b5 == hash_result[4])&&(saved_b6 == hash_result[5])&&(saved_b7 == hash_result[6])&&(saved_b8 == hash_result[7]);
    
    return same;
}






