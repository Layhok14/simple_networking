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

fd_set read_fds, write_fds;
int conn_fd, listen_fd, free_storage;
// server side: One server. Do the reading.
// client side: Multiple clients connect to the server for reading and writing.

typedef enum{
    CONNECTED,
    DISCONNECTED,
    REJECTED,
} fd_state_e;

// what are the other cases of the rejeting if one case is not able ot write to the client socket?

typedef struct{
    int fd;
    fd_state_e state;
    bool space_allocated;
    char* buffer;
}client_socket_state;

// - func: init_client_arr
// - description: initialize the client and default value
client_socket_state* init_client_state_arr(void){
    client_socket_state* c_states = malloc(MAX_CAPACITY*sizeof(client_socket_state));
    for(size_t i = 0; i< MAX_CAPACITY;i++){
        c_states[i].state = DISCONNECTED;
        c_states[i].space_allocated = false;
        c_states[i].buffer = NULL;
    }
    return c_states;
}

// - func: init_client
// - description: initialize the client and add the new client to the read_fds set.
// void init_client(){
//     int client_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if(client_socket == -1 ){
//         perror("client socket");
//         return;
//     }
//     FD_SET(client_socket, &read_fds);
//     return;
// }
void add_client(client_socket_state* c_states, int fd, int arg_buffer_size){
   for(size_t i = 0; i < MAX_CAPACITY; i++) {
        if(c_states[i].state == DISCONNECTED || c_states[i].state == REJECTED){
            int allocate_size = arg_buffer_size? arg_buffer_size: BUFFER_SIZE;
            c_states[i].buffer =  malloc(sizeof(char) * allocate_size);
            if(c_states[i].buffer == NULL){
                perror("allocate memory for the buffer of the client");
                return;
            }
            c_states[i].state = CONNECTED;
            FD_SET(fd,&read_fds);
            break;
        }
    }
}

// - func: find_free_memory_slot
// - description: find free memory slot from avaialble spaces in the set, if not, allocate a new one for the new file descriptor to read into.
// void find_free_memory_slot(int fd, client_socket_state* client_state_arr){
//     for(int i = 0; i< MAX_CAPACITY; i++){
//         if(!client_state_arr->space_allocated){
//             client_state_arr[i].space_allocated = true;
//
//         }
//     }
//     return;
// }

int main(int argc, char* argv[]){
    if(argc==4) {
        printf("Error usage: <ipv4 address>, <client_buffer_size>, <cleint_address> %s.\n", argv[0]);
        return -1;
    }
    for(size_t i = 0; i < argc;i++) {
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
    client_socket_state* client_state_arr = init_client_state_arr();
    // allocate the memory for the client
    int server_socket =  socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in server_info = {AF_INET, (in_port_t) CLIENT_PORT, inet_addr(LOCALHOST)};
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
    client_socket_state* client_states_arr = init_client_state_arr();
    struct sockaddr_in client_info = {0};
    size_t client_add_size = 0;
    //create connection for the client side to the server side.
    int accept_fd = accept(server_socket, (struct sockaddr*) &client_info, (socklen_t *) &);
    if(accept_fd==-1){
        perror("accept");
        close(server_socket);
        return -1;
    }
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 1000;
    while(1){
        // reinitialize the fd as each iteration, as the file descriptors are modified in place using the select function. 
        FD_ZERO(&read_fds);
        FD_ZERO(&write_fds);
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(client_socket==-1){
            perror("client socket");
            return -1;
        }
        add_client(client_states_arr, client_socket,);
    }
    // check if the server accept the connection with the client. 
    return 0;
}
