#include<stdio.h>
#include "kv_table.h"
#include <assert.h>
int main(){
    // kv_table* employeeTable = kv_init(6);
    // kv_table* departmentTable = kv_init(4);
    // printf("employeeTable capacity: %ld\n", employeeTable->capacity);
    // printf("employeeTable count: %ld\n", employeeTable->count);
    // printf("employeeTable data_ptr: %p\n", employeeTable->data);
    kv_table* db = kv_init(16);
    assert(db != NULL);
    assert(db->capacity == 16);
    assert(db->count == 0); 
    //printf("count: %ld\n",db->count);
    char* key = "name";
    char* key2 = "student";
    int q1 = kv_put(db,key,"Layhok");
    int q2 = kv_put(db, key,"Nay");
    int q3 = kv_put(db, key2, "sth");
    printf("element count: %ld\n", db->count);
    c_string_container get_val = kv_get(db,key2);
    for(size_t i =0; i< get_val.size; ++i){
        printf("data %ld row: %s %s.\n", i, key2, get_val.arr[i]);
    }
    int delete = kv_delete(db, key);
    c_string_container get_update = kv_get(db,key);
    for(size_t i =0; i< get_update.size; ++i){
        printf("data %ld row: %s %s.\n", i, key, get_update.arr[i]);
    }
    printf("element count: %ld\n", db->count);
    // kv_free(db);
    return 0;
}
//TODO:
//1. Check the logic of count 
//2. check why the loop doesn't print.
