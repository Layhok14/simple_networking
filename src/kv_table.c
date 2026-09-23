#include "kv_table.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
kv_table* kv_init(size_t capacity){
    kv_table* table = malloc(sizeof(kv_table));
    table->capacity = capacity;
    table->count=0;
    table->data = calloc(capacity,sizeof(kv_entry));
    if(table->data==NULL){
    }
    return table;
    return NULL;
 }
void kv_free(kv_table* table){
    if(table ==NULL){
        printf("Data is already NULL!\n");
        return; 
    }
    if(table->data!=NULL){
        free(table->data);
        table->data =NULL;
        printf("The table has been freed.\n");
    }else{
        printf("maybe we have to check the data first!\n");
    }
    free(table);
    table=NULL;
    printf("Look like table is freed now.\n");
    printf("Now it is outside the checking now.\n");
}
