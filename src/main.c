#include<stdio.h>
#include "kv_table.h"
#include <assert.h>

int main(){
    // kv_table* employeeTable = kv_init(6);
    // kv_table* departmentTable = kv_init(4);
    // printf("employeeTable capacity: %ld\n", employeeTable->capacity);
    // printf("employeeTable count: %ld\n", employeeTable->count);
    // printf("employeeTable data_ptr: %p\n", employeeTable->data);
    kv_table* table_ref = kv_init(4);
    kv_table table = *table_ref;
    //printf("count: %ld\n",table->count);
    char* key = "name";
    char* key2 = "student";
    int q1 = kv_put(&table,key,"Layhok");
    check_operation(q1);
    int q2 = kv_put(&table, key,"Nay");
    check_operation(q2);
    int q3 = kv_put(&table, key2, "sth");
    check_operation(q3);
    printf("element count: %ld\n", table.count);
    c_string_container get_val = kv_get(&table, key2);
    printf("get element arr size: %ld\n", get_val.size);
    for(size_t i =0; i< get_val.size; ++i){
        printf("data %ld row: %s %s.\n", i, key2, get_val.arr[i]);
    }
    int delete = kv_delete(&table, key);
    check_operation(delete);
    c_string_container get_update = kv_get(&table,key);
    printf("get element arr size: %ld\n", get_update.size);
    for(size_t i =0; i< get_update.size; ++i){
        printf("data %ld row: %s %s.\n", i, key, get_update.arr[i]);
    }
    printf("element count: %ld\n", table.count);
    kv_free(&table);
    return 0;
}
