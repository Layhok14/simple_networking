#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/select.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include <stdbool.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096
#define MAX_CAPACITY 20
// server side: One server. Do the writing.
// client side: Multiple clients connect to do the reading.

// read_fds: set for the server to read the data from.
// write_fds: set of fd for the server to write the data to.
fd_set read_fds, write_fds;

int conn_fd, listen_fd; 

typedef enum{
    CONNECTED,
    DISCONNECTED,
} fd_state_e;

typedef struct{
    int fd;
    fd_state_e state;
    char* buffer;
}server_socket_state;
typedef struct{
    int fd;// but if the same socket is reused then the old info is lost...?
    char* buffer;
}client_sates;
// - func: init_client_arr
// - description: initialize the client and default value
server_socket_state* init_client_state_arr(void){
    server_socket_state* c_states = malloc(MAX_CAPACITY*sizeof(server_socket_state));
    for(size_t i = 0; i< MAX_CAPACITY;i++){
        c_states[i].state = DISCONNECTED;
        c_states[i].buffer = NULL;
    }
    return c_states;
}
// func; add_client
// description: add the client to the read && write fd set.
void add_client(server_socket_state* c_states, int fd, int arg_buffer_size, char* text){
    for(size_t i = 0; i < MAX_CAPACITY; i++){
        if(c_states[i].state = DISCONNECTED){
            c_states[i].buffer =  malloc(sizeof(char) * arg_buffer_size);
            if(c_states[i].buffer == NULL){
                perror("allocate memory for the buffer of the client");
                return;
            }
            printf("size of the buffer: %ld\n", sizeof(c_states[i].buffer));
            char* new_text;
            // ensure thre is no problem with the lifetime of the argument var.
            strcpy(new_text, text);
            c_states[i].buffer = new_text;
            c_states[i].fd = fd;
            c_states[i].state = CONNECTED;
            FD_SET(fd,&read_fds);
            FD_SET(fd, &write_fds);
            break;
            }
        }
}

// - func: find_free_memory_slot
// - description: find free memory slot from avaialble spaces in the set, if not, allocate a new one for the new file descriptor to read into.
// void find_free_memory_slot(int fd, server_socket_state* client_state_arr){
//     for(int i = 0; i< MAX_CAPACITY; i++){
//         if(!client_state_arr->space_allocated){
//             client_state_arr[i].space_allocated = true;
//
//         }
//     }
//     return;
// }

int main(int argc, char* argv[]){
    // in this case, we will let the server do the read and write back to the client before finishig the task with the client. we will try to asyn the process in the future, maybe.
    if(argc!=2) {
        printf("Error usage: <text to send to the server> %s.\n", argv[0]);
        return -1;
    }
    for(size_t i = 0; i < argc; i++){
        if(strcmp(argv[i], "--help")==0){
            int message_fd = open("./inc.help_message.txt", O_RDONLY);
            char message_buffer[MESSAGE_BUFFER_SIZE];
            ssize_t help_meesage_read = read(message_fd, &message_buffer, MESSAGE_BUFFER_SIZE);
            if(help_meesage_read==-1){
                perror("Read the help message");
                return -1;
            }
            printf("%s\n", message_buffer);
        }
    }
    char* client_text = argv[1];
    server_socket_state* client_state_arr = init_client_state_arr();
    // allocate the memory for the client
    int server_socket =  socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in server_info = {AF_INET, (in_port_t) SERVER_PORT, inet_addr(LOCALHOST)};
    if(bind(server_socket, (struct sockaddr *) &server_info, sizeof(server_info))==-1){
        perror("bind");
        close(server_socket);
        return -1;
    }
    int listen_fd = listen(server_socket,MAX_CAPACITY);
    if(listen_fd==-1){
        perror("listen");
        close(server_socket);
        return -1;
    }
    server_socket_state* client_states_arr = init_client_state_arr();
    struct sockaddr_in client_info = {0};
    while(1){
        int accept_fd = accept(server_socket, (struct sockaddr*) &client_info, (socklen_t *) &(client_info));
        // check if the server accept the connection with the client. 
        if(accept_fd==-1){
            perror("accept");
            close(server_socket);
            return -1;
        }
        //check if the fd set has space available
        if(accept_fd >= FD_SETSIZE){
            close(accept_fd);
        }else{
            add_client(client_states_arr,accept_fd, strlen(client_text), client_text);
        }
        int monitor_fd = select(accept_fd, &read_fds, &write_fds, NULL, NULL);
        if(!monitor_fd){
            perror("select");
        }else{
            int is_set = FD_ISSET(accept_fd, &read_fds);
            // check if the adding of the client will also be unset back.  
        }
         

       
    }
   return 0;
}
