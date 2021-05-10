#include "Documentor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <unordered_map>
using namespace std;
int curr_id = 0;
unordered_map<int, unordered_map<uintptr_t, size_t>> my_Documentation; 


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

