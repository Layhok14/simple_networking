#ifndef EMPLOYEE_DB_TABLE
#define EMPLOYEE_DB_TABLE
#include "string_container.h"
# define check_operation(var) handle_error(var, #var)
#ifndef HASH_TABLE_LOAD_FACTOR
#define HASH_TABLE_LOAD_FACTOR 0.75
#endif
typedef struct {
	char* key;
    char* val;
}kv_entry;

typedef struct{
	size_t capacity;
    size_t count;
    kv_entry *entry; 
}kv_table;
kv_table* kv_init(size_t capacity);
void kv_free(kv_table* table);
void handle_error(int result, const char* var_name);
int kv_put(kv_table* table, char* key, char* val);
c_string_container kv_get(kv_table* table,char* key);
int kv_delete(kv_table*table, char* key);
int kv_delete(kv_table* table,char* key);
void rehash_hash_table(kv_table** container_ref);
#endif
