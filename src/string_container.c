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
    char** new_arr = (char **) realloc(new_arr, (container->size+1) * sizeof(c_string_container)); 
    if(!new_arr){
        new_arr = (char **) malloc(sizeof(c_string_container *));
        if(!new_arr){
            return -1;
        }
        else{
            // perform shallow copy which maps to the same address for each element.
            for(size_t counter = container->size;counter--;){
                new_arr[counter]= container->arr[counter];
            }
            if(container->size){
                // just free the container not each element of the container.
                free(container->arr);
            }
        }
    }
    new_arr[container->size] = malloc(sizeof(char)*(text_length+1));
    if(!new_arr){
        return -1;
    }
    memcpy(new_arr[container->size], text,text_length);
    new_arr[container->size][length] = '\0';
    container->arr = new_arr;
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
    c_string_container* container;     
    char* input_end = input+strlen(input);
    init_c_string_container(container);
    length = strlen(input);
    char* endpoint;
    while(endpoint =strchr(input,delimeter)){
        int result = add_element_to_c_string_container(container, input, endpoint-input);
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
