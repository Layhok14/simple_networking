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
    printf("count: %ld\n",db->count);
    char* key = "name";
    int first_q = kv_put(db,key,"Layhok");
    printf("the result is %d.\n",first_q);
    kv_put(db, key,"Nay");
    printf("count: %ld\n",db->count);
    printf("capacity: %ld\n",db->capacity);
    c_string_container* get_val = kv_get(db,key);
    for(size_t i =0; i< get_val->size; ++i){
        printf("data %ld row: %s %s.\n", i, key, get_val->arr[i]);
    }
    // kv_free(db);
    return 0;


}
