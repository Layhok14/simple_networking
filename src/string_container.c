#include "stringContainer.h"
#include<stdlib.h>
#include<string.h>
void init_c_string_container(c_string_container *container){
    container->size =0;
    container->arr = NULL;
}
//function: add_element_to_c_string_container
//@brief:
int add_element_to_c_string_container(c_string_container *container, const char* text,size_t text_length){
    //allocate the mem for an array pointer
    char** new_arr = (char **) realloc(container->arr, (container->size+1) * sizeof(char *));
    if(!new_arr){
        return -1;
    }
    container->arr = new_arr;
    // allocate the mem for the string itsel to be inserted at the array pointer.
    container->arr[container->size] = malloc(sizeof(text_length+1));
    if(!container->arr[container->size]){
        return -1;
    }
    memcpy(container->arr[container->size], text, text_length);
    container->arr[container->size][text_length] = '\0';
    container->size++;
    return 0;
}
//function:
void free_c_string_container(c_string_container* container){
    if(container==NULL) {
        return;
    }
    for(size_t i = container->size;i--;){
        free(container->arr[i]);
    }
    free(container->arr);
    init_c_string_container(container);
}
c_string_container substrings(char* input, const char delimeter){
    c_string_container* container = NULL;
    char* input_end = input+strlen(input);
    init_c_string_container(container);
    char* endpoint=NULL;
    while((endpoint = strchr(input, delimeter))){
        add_element_to_c_string_container(container, input, endpoint-input);
        while(strchr(endpoint, delimeter)== endpoint){
            ++endpoint;
        }
        input = endpoint;
    }
    if(input<input_end){
        add_element_to_c_string_container(container,input,(input_end-input));
    }
    return *container;
}
