#ifndef EMPLOYEE_DB_TABLE
#define EMPLOYEE_DB_TABLE
#include "stringContainer.h"

typedef struct {
	char* key;
    char* val;
}kv_entry;

typedef struct{
	size_t capacity;
    size_t count;
    kv_entry *entry; 
}kv_table;
kv_table *kv_init(size_t capacity);
void kv_free(kv_table* table);
int kv_put(kv_table* table, char* key, char* val);
c_string_container* kv_get(kv_table* table,char* key);
int kv_delete(kv_table*table, char* key);
#endif
