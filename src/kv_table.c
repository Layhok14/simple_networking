#include "kv_table.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TOMBSTONE ((char *)0x1)
// for simplicity, the progam will just use the hash table for storing and interracting data. there won't be implementation of B+-Tree yet.

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
    size_t hash = 0x01ebeffbeeac; 
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
// note: this applies the open address approach using lienar probing.
int kv_put(kv_table* table, char* key, char* val){
    if(!table || !key || !val){
        return -1;
    }
    size_t index = hash(key, table->capacity);
    int frist_tombstone_ind = -1;
    for(size_t i =0; i< table->capacity; i++){
        size_t real_index = (i+index) % table->capacity;
        // printf("Entry val pointer, val: %p, %s. \n",table->entry, table->entry->val);
        kv_entry* entries = &table->entry[real_index];
        // if the key is null, create new element.
        if(entries->key == NULL){
            // printf("case 1: NULL.\n");
            size_t insertIndex = (frist_tombstone_ind !=-1)? (size_t) frist_tombstone_ind: real_index;
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
            // printf("case 2:TOMBSTONE.\n");
            if(frist_tombstone_ind==-1){
                frist_tombstone_ind=real_index;
            }
            continue;
        }
        // find the existing matching key, then go the next address.
        if(entries->key && strcmp(entries->key,key)==0){
            // printf("case 3: found matches.\n");
            // char* newVal = strdup(val);
            // if(!newVal) {
            //     free(newVal);
            //     return -1;
            // }
            // free(entries->val);
            // entries->val = newVal;
            printf("Already filled. Going to next one.\n");
            continue;
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
c_string_container kv_get(kv_table* table, char* key){
    c_string_container result;
    init_c_string_container(&result);
    // size_t index = hash(key,table->capacity);
    printf("==========================================\n");
    for(size_t i = 0;i< table->capacity;i++){
        size_t real_index = (i)%table->capacity;
        char* entry_key = table->entry[real_index].key;
        char* entry_val = table->entry[real_index].val;
        if(entry_val&&strcmp(entry_key,key)==0){
        printf("Adding...\n");
        printf("size of result: %ld\n", result.size);
        int add_result = add_element_to_c_string_container(&result, entry_val, strlen(entry_val));
        // printf("adding result is: %d\n", add_result);
        // printf("Result added: %s", result.arr[result.size-1]);
        }
    }
    return result;
}
//func kv_delete
//- table: pointer to the db.
//- key: pointer to the key value to delete from the db.
//returns: 0 if success and -1 otehrwise.
//Note: For simplicity, the key given will delete all related values.

int kv_delete(kv_table* table,char* key){
    size_t index = hash(key,table->capacity);
    //replace the value with the value of TOMBSTONE
    c_string_container get_val = kv_get(table,key);
    if(get_val.size==0){
        return -1;
    }
    for(size_t i = 0; i < get_val.size;i++){
        size_t real_index = (index+i)%table->capacity;
        kv_entry* entry = &table->entry[real_index];
        char* entry_key = entry->key;
        char* entry_val = entry->val;
        if(strcmp(entry_key,key)==0){
            if(entry_val){
                free(entry_key); 
                free(entry_val); 
                entry_key = TOMBSTONE;  
                entry_val = NULL;
            }
        }
    } 
    return 0;
}
