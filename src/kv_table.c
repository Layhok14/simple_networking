#include "kv_table.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOMBSTONE ((char *)0x1)

// func: hash
// description: a hashing function for hash tbale when inserting.
// params:
//      - val: pointer to the key to hash.
//      - capacity: the avaible size of the hash table.
// returns: hash of the key with the cap to the size of the capacifty of the hash table.
size_t hash(char* val, size_t capacity){
    size_t hash = 0x01ebeffbeeac; 
    while(*val){
        hash^= *val;
        hash += *val;
        val++;
    }
    return hash % capacity;
}

// func: handle_error 
// description: this is to check for error return by the function impllemented in the project.
// params:
//      - result: number returns from the functio of adding operation to the data structure.
// returns: statement of success if it is the success code, and code error with statement if otherwise.
void handle_error(int result, const char* var_name){
    if(result == 0){
        printf("successful operation for var: %s\n",var_name);
    }else{
        printf("Result status code: %d for var: %s.\n", result, var_name);
    }
}
// func: kv_init
// desctiption: initialize the hash table.
// capacity: size of the allocated slots for the hash table.
// returns: return table pointer upon success, otherwise NULL.
kv_table* kv_init(size_t capacity){
    kv_table* table = malloc(sizeof(kv_table));
    if(!table){
        return NULL;
    }
    table->capacity = capacity;
    table->count=0;
    table->entry = calloc(capacity,sizeof(kv_entry));
    if(table->entry==NULL){
        free(table);
        return NULL;
    }
    return table;
}

// function: rehash_hash_table
// description: create a new hash table with a new size and copy all elements in the old hash table to the new one.point to the new hash table and free the old table.
// params:
//      - container: the old hash table.
// returns: new a hash table.
void rehash_hash_table(kv_table** container_ref){
    kv_table* container = *container_ref;
    size_t new_capacity = 2 * container->capacity;
    kv_table* new_table = kv_init(new_capacity);
    for(size_t i = 0; i < container->capacity;i++){
        char* pos_key = container->entry[i].key;
        char* pos_val = container->entry[i].val;
        if(pos_key!=NULL && pos_key!=TOMBSTONE){
            int pos_add = kv_put(new_table, pos_key, pos_val);
            check_operation(pos_add);
        }
    }
    kv_free(container);
    *container_ref = new_table;
}

// function: kv_free
// params:
//     - table: the pointer to the hash table.
// returns: message based on the condition of freeing and chekcing of freed memory.
void kv_free(kv_table* table){
    if(table ==NULL){
        printf("Data is already NULL!\n");
        return; 
    }
    if(table->entry!=NULL){
        for(size_t i = 0; i< table->capacity;i++){
            char* key = table->entry[i].key;
            char* val = table -> entry[i].val;
            if(key==NULL){
                continue;
            }
            if(val==NULL){
                continue;
            }
            if(key!=NULL && key!=TOMBSTONE){
                free(key);
            }
            if(val!=NULL){
                free(val);
            }
        }
        free(table->entry);
        table->entry=NULL;
    }else{
        printf("maybe we have to check the data first!\n");
    }
    free(table);
    table=NULL;
    printf("The table has been freed.\n");
}

// function: kv_put
// description: insert the new element into the hash table. This applies the open address approach using lienar probing.
// params:
//      table: the pointer to the hash table. 
//      key: the pointer to the key to insert
//      val: the pointer ot the value to insert into the hash table.
// returns: the index of the key, otherwise on error -1.
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
            // check if the the size is greater than the laod factor.
            size_t threshold_count = HASH_TABLE_LOAD_FACTOR * table->capacity;
            if(table->count >= threshold_count){
                rehash_hash_table(&table);
                printf("rehased the table\n");
                printf("new capacity of the table: %ld\n", table->capacity);
            }
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
// function: kv_get
// params:
// - table: the pointer to the db.
// - key: the pointer to the key to lookup to get the value.
// returns: value if there is a match, and null if otherwise.
c_string_container kv_get(kv_table* table, char* key){
    c_string_container result;
    init_c_string_container(&result);
    // size_t index = hash(key,table->capacity);
    printf("==========================================\n");
    for(size_t i = 0;i< table->capacity;i++){
        size_t real_index = i;
        char* entry_key = table->entry[real_index].key;
        char* entry_val = table->entry[real_index].val;
        if(entry_val&&strcmp(entry_key,key)==0){
        printf("Adding...\n");
        printf("size of result: %ld\n", result.size);
        int add_result = add_element_to_c_string_container(&result, entry_val, strlen(entry_val));
        check_operation(add_result);
        // printf("adding result is: %d\n", add_result);
        // printf("Result added: %s", result.arr[result.size-1]);
        }
    }
    return result;
}
// function: kv_delete
// Description: The key given will delete all related values.
// params:
//      - table: pointer to the db.
//      - key: pointer to the key value to delete from the db.
// returns: 0 if success and -1 otherwise.

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
                table->count--;
            }
        }
    }
    return 0;
}
