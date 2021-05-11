#include "Documentor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unordered_map>
#include "sha1_arm.h"
#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
using namespace std;
int curr_id = 0;
unordered_map<int, unordered_map<uintptr_t, size_t>> my_Documentation;
unordered_map<int, uintptr_t> my_rootptr_map;  
unordered_map<int, uintptr_t> my_pac_map; 
uint8_t saved_b1=0;
uint8_t saved_b2=0;
uint8_t saved_b3=0;
uint8_t saved_b4=0;
uint8_t saved_b5=0;
uint8_t saved_b6=0;
uint8_t saved_b7=0;
uint8_t saved_b8=0;

typedef struct {
    uint8_t hash_result[8];
    (const uint8_t*) block_msg;
    size_t length;
} hash_struct;



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

void Insert_newBlock_withID(int id, uintptr_t pointer_addr, size_t size, int root) {
    if(root==1){
        my_rootptr_map[id] = pointer_addr;
    }
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

//add a pac, pacresult in result
uintptr_t pac_add(uintptr_t my_pointer, uint64_t context){
    uintptr_t result; 
    __asm  volatile(
	"str x3, [sp, #-8]! \n\t"
	"mov x3, %[input_pointer] \n\t"
	"str x4, [sp, #-8]! \n\t"
	"mov x4, %[noise] \n\t"
	"PACDA x3, x4 \n\t"
	"mov %0, x3 \n\t"
	"ldr x4, [sp], #8 \n\t"
	"ldr x3, [sp], #8 \n\t"
	: "=r" (result)
	: [input_pointer] "r" (my_pointer), [noise] "r" (context)
    );
    return result;
}

//gives a pacpointer, return pointer if pac is correct
uintptr_t aut_add(uintptr_t my_pointer, uint64_t context){
    uintptr_t result;
    __asm  volatile(
	"str x3, [sp, #-8]! \n\t"
	"mov x3, %[input_pointer] \n\t"
	"str x4, [sp, #-8]! \n\t"
	"mov x4, %[noise] \n\t"
	"AUTDA x3, x4 \n\t"
	"mov %0, x3 \n\t"
	"ldr x4, [sp], #8 \n\t"
	"ldr x3, [sp], #8 \n\t"
	: "=r" (result)
	: [input_pointer] "r" (my_pointer), [noise] "r" (context)
    );
    return result;
}

void hash_function(void* args){
    hash_struct *actual_args = args;
    uint32_t state[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    sha1_process_arm(state, actual_args->block_msg, actual_args->length);
    actual_args->hash_result[0] = (uint8_t)(state[0] >> 24);
    actual_args->hash_result[1] = (uint8_t)(state[0] >> 16);
    actual_args->hash_result[2] = (uint8_t)(state[0] >>  8);
    actual_args->hash_result[3] = (uint8_t)(state[0] >>  0);
    actual_args->hash_result[4] = (uint8_t)(state[1] >> 24);
    actual_args->hash_result[5] = (uint8_t)(state[1] >> 16);
    actual_args->hash_result[6] = (uint8_t)(state[1] >>  8);
    actual_args->hash_result[7] = (uint8_t)(state[1] >>  0);
    
}

void compute_Hash(int id, int compare){

    //uint8_t *hash_result = (uint8_t*)malloc(8 * sizeof(uint8_t));
    uint8_t hash_result[8];

    int number_Block = my_Documentation[id].size();
    unordered_map<uintptr_t, size_t> my_map = my_Documentation[id];
    uint8_t* hash_sum = (uint8_t*)malloc(8*number_Block * sizeof(uint8_t));
    
    int index = 0;
    
    //multithread solution
    pthread_t* threads_hash =(pthread_t*)malloc(my_map.size()*sizeof(pthread_t));
    unordered_map<int, hash_struct*> index_struct_map;
    int map_index = 0;
    for (auto it : my_map){       
        hash_struct* hash_struct_helper = (hash_struct*)malloc(sizeof(hash_struct));
	hash_struct_helper->block_msg = (const uint8_t*)it.first;
	hash_struct_helper->length = it.second;	
	pthread_create(&threads_hash[map_index], NULL, hash_function, hash_struct_helper);
	index_struct_map[map_index] = hash_struct_helper;
	map_index=map_index+1;
	/*
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
        index = index+1;*/
																	 
     }
     
     for (int i = 0; i < my_map.size(); i++){
         pthread_join(threads_hash[i], NULL);
         
         hash_sum[index]=index_struct_map[i].hash_result[0];
         index = index+1;
         hash_sum[index]=index_struct_map[i].hash_result[1];
         index=index+1;
         hash_sum[index]=index_struct_map[i].hash_result[2];
         index=index+1;
         hash_sum[index]=index_struct_map[i].hash_result[3];
         index = index+1;
         hash_sum[index]=index_struct_map[i].hash_result[4];
         index = index+1;
         hash_sum[index]=index_struct_map[i].hash_result[5];
         index = index+1;
         hash_sum[index]=index_struct_map[i].hash_result[6];
         index = index+1;
         hash_sum[index]=index_struct_map[i].hash_result[7];
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
     
     hash_result[0] = b1;
     hash_result[1] = b2;
     hash_result[2] = b3;
     hash_result[3] = b4;
     hash_result[4] = b5;
     hash_result[5] = b6; 
     hash_result[6] = b7;
     hash_result[7] = b8;
     
     if(compare==1){
         //printf("SHA1 hash of empty message: ");
         //printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",hash_result[0], hash_result[1], hash_result[2], hash_result[3], hash_result[4], hash_result[5], hash_result[6], hash_result[7]);  
         //printf("saved SHA1 hash of empty message: ");
         //printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",saved_b1, saved_b2, saved_b3, saved_b4, saved_b5, saved_b6, saved_b7, saved_b8);
        uint64_t context;
        for (int hash_index=0; hash_index<8; hash_index++){
            context = (context << 8) | hash_result[hash_index];
        }
        uintptr_t pacptr = my_pac_map[id];
        //context = context - 1;
	uintptr_t aut_result = aut_add(pacptr, context);
	*((int*)aut_result);
	//printf("ptr after aut %" PRIxPTR "\n", (uintptr_t)aut_result);
	//printf("%d\n", *((int*)aut_result));
        
	 /*bool same = (saved_b1 == hash_result[0])&&(saved_b2 == hash_result[1])&&(saved_b3 == hash_result[2])&&(saved_b4 == hash_result[3])&&(saved_b5 == hash_result[4])&&(saved_b6 == hash_result[5])&&(saved_b7 == hash_result[6])&&(saved_b8 == hash_result[7]);
	assert(same==1);*/
     }else{
        /*saved_b1 = hash_result[0];
        saved_b2 = hash_result[1];
        saved_b3 = hash_result[2];
        saved_b4 = hash_result[3];    
        saved_b5 = hash_result[4];    
        saved_b6 = hash_result[5];    
        saved_b7 = hash_result[6];    
        saved_b8 = hash_result[7]; */
       
        uint64_t context;
        for (int hash_index=0; hash_index<8; hash_index++){
            context = (context << 8) | hash_result[hash_index];
        }
        
        uintptr_t rootptr = my_rootptr_map[id];
        uintptr_t pac_result = pac_add(rootptr, context);
        //printf( "pac_result %" PRIxPTR "\n", (uintptr_t)  pac_result);
        my_pac_map[id] = pac_result;

       //printf("SHA1 hash of empty message: ");
       //printf("%02X%02X%02X%02X%02X%02X%02X%02X\n",saved_b1, saved_b2, saved_b3, saved_b4, saved_b5, saved_b6, saved_b7, saved_b8);    
     } 
         
     free(hash_sum);
}







