#include "kv_table.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TOMBSTONE ((char *)0x1)
// func: kv_init
// capacity: size of the allocated slots for the db.
// returns: return table pointer upon success, otherwise NULL.
kv_table* kv_init(size_t capacity){
    kv_table* table = malloc(sizeof(kv_table));
    table->capacity = capacity;
    table->count=0;
    table->entry = calloc(capacity,sizeof(kv_entry));
    if(table->entry==NULL){
        return NULL;
    }
    return table;
 }
// func: kv_free
// table: the pointer to the db/table.
// returns: message based on the condition of freeing and chekcing of freed memory.
void kv_free(kv_table* table){
    if(table ==NULL){
        printf("Data is already NULL!\n");
        return; 
    }
    if(table->entry!=NULL){
        free(table->entry);
        table->entry=NULL;
        printf("The table has been freed.\n");
    }else{
        printf("maybe we have to check the data first!\n");
    }
    free(table);
    table=NULL;
    printf("Look like table is freed now.\n");
    printf("Now it is outside the checking now.\n");
}
// func hash
// -val: pointer to the key to hash.
// - capacity: the avaible size of the db.
// returns: hash of the key with the cap to the size of the capacifty of the db/table.
size_t hash(char* val, size_t capacity){
    size_t hash = 0xeffbeeac; 
    while(*val){
        hash^= *val;
        hash += *val;
        val++;
    }
    return hash % capacity;
}

// func kv_put:
// table: the pointer to the  db or the table. 
// key: the pointer to the key to insert
// val: the pointer ot the value to insert into the db.
// returns: the index of the key, otherwise on error -1.
int kv_put(kv_table* table, char* key, char* val){
    if(!table || !key || !val){
        return -1;
    } 
    size_t index = hash(key, table->capacity);
    size_t frist_tombstone_ind = -1;
    for(size_t i =0; i< table->capacity; i++){
        size_t real_index = (i+index)%table->capacity;
        kv_entry* entries = &table->entry[real_index];
        // if the key is null, create new element.
        if(!entries->key){
            // printf("case 1\n");
            size_t insertIndex = (frist_tombstone_ind !=-1)? frist_tombstone_ind: real_index;
            kv_entry* new = &table->entry[insertIndex];
            char* newKey = strdup(key);
            char* newVal = strdup(val);
            if(!newKey || !newVal) {
                free(newKey);
                free(newVal);
                return -1;
            }
            new->key = newKey;
            new->val = newVal;
            table->count++;
            return 0;
        }
        // if the key is tombstone, then we set the index and go to next iteration.
        if(entries->key==TOMBSTONE){
            // printf("case 2\n");
            if(frist_tombstone_ind==-1){
                frist_tombstone_ind=real_index;
            }
            continue;
        }
        // find the existing matching key, then update
        if(entries->key && !strcmp(entries->key,key)){
            // printf("case 3/n");
            char* newVal = strdup(val);
            if(!newVal) {
                free(newVal);
                return -1;
            }
            free(entries->val);
            entries->val = newVal;
        }
    } 
    //if there are all occupied with one tombstone left.
    if(frist_tombstone_ind!=-1){
        kv_entry* entry = &table->entry[frist_tombstone_ind];
        char* newKey = strdup(key);
        char* newVal = strdup(val);
        if(!newKey || !newVal){
            free(newKey);
            free(newVal);
            return -1;
        }
        entry->key = newKey;
        entry->val = newVal;
        return 0;
    }
    //if the db is occupied with no space to add anything.
    return -2;
}
// func kv_get
// - table: the pointer to the db.
// - key: the pointer to the key to lookup to get the value.
// returns: value if there is a match, and null if otherwise.
c_string_container* kv_get(kv_table* table, char* key){
    size_t index = hash(key,table->capacity);
    int pos = 0;
    c_string_container* result; 
    init_c_string_container(result);
    for(size_t i = 0; i < table->capacity;i++){
        printf("Iteration: %ld\n",i);
        size_t real_index = (index+i) % table->capacity; 
        char* val = table->entry[real_index].val;
        if(val){
            add_element_to_c_string_container(result, val, strlen(val));
        }
    }
    return result;
}
//func kv_delete
//- table: pointer to the db.
//- key: pointer to the key value to delete from the db.
//returns: 0 if success and -1 otehrwise.

// int kv_delete(kv_table*,char* key){
//
// }
