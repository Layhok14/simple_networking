#include<stdio.h>
#include"kv_table.h"
#include <assert.h>
int main(){
    kv_table* employeeTable = kv_init(6);
    kv_table* departmentTable = kv_init(4);
    printf("employeeTable capacity: %ld\n", employeeTable->capacity);
    printf("employeeTable count: %ld\n", employeeTable->count);
    printf("employeeTable data_ptr: %p\n", employeeTable->data);
    kv_table* db = kv_init(16);
    assert(db != NULL);
    assert(db->capacity == 16);
    assert(db->count == 0);
    kv_free(db);
    return 0;

}
