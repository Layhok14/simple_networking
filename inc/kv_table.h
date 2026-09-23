#ifndef EMPLOYEE_DB_TABLE
#define EMPLOYEE_DB_TABLE

#include <stddef.h>

typedef struct {
	int key;
    int val;
}kv_entry;

typedef struct{
	size_t capacity;
    size_t count;
    kv_entry *data; 
}kv_table;

kv_table *kv_init(size_t capacity);

void kv_free(kv_table* table);

#endif
