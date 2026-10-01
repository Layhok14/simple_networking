#include <stddef.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "socket.h"
void handle_client(int socket_fd){
    char buffer[4096]  = {0};
    proto_type_header_e* header = (proto_type_header_e *) &buffer;
    header->type = htonl(PROTO_HELLO);
    header->length = sizeof(int);
    size_t allocated_length = header->length;
    header->length = htonl(header->length);
    int *data = (int *) &header[1];
    *data = htonl(1);
    write(socket_fd, header, allocated_length + sizeof(proto_type_header_e));
    close(socket_fd);
}

int start_server(char* address){
    struct sockaddr_in server_info = {0};
    struct sockaddr_in client_info = {0};
    int client_size = 0;
    server_info.sin_family  = AF_INET;
    server_info.sin_port = htons(PORT);
    server_info.sin_addr.s_addr = inet_addr(address);
    int server_socket = socket(AF_INET ,SOCK_STREAM,0);
    if(server_socket==-1){
        return -1;
    }
    //bind
    if(bind(server_socket,(struct sockaddr *) &server_info, sizeof(server_info)) ==-1){
        perror("bind");
        close(server_socket);
        return -1;
    }
    //listen
    if(listen(server_socket, BACKLOG)==-1){
        perror("listen");
        close(server_socket);
        return -1;
    }
    while(1){
        //accept
        int cfd = accept(server_socket,(struct sockaddr *) &client_info, (socklen_t *)&client_size);
        if(cfd==-1){
            perror("accept");
            close(server_socket);
            return -1;
        }
        handle_client(cfd);
    }
    close(server_socket);
    return 0;
}
int main(int argc, char* argv[]){
    if(argc!=2){
        printf("usage: <ip4 address>: %s\n", argv[0]);
        return -1;
    }
    start_server(argv[1]);
    printf("socker.\n");
    return 0;
}
