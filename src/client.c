#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "socket.h"

void handle_server(int socket_fd){
    char buffer[4096] = {0};
    proto_type_header_e* header = (proto_type_header_e *) buffer;
    
    // Read packet from server
    ssize_t bytes_read = read(socket_fd, header, sizeof(proto_type_header_e) + sizeof(int));
    if (bytes_read <= 0) {
        perror("read failed or server disconnected");
        return;
    }

    // Convert from network to host order for reading
    uint32_t recv_type = ntohl(header->type);
    uint32_t recv_length = ntohl(header->length);

    int *data = (int *) &header[1];
    int recv_data = ntohl(*data); // Convert payload to host order

    // Validate the protocol and data
    if (recv_type != PROTO_HELLO || recv_data != 1) {
        printf("Mismatch protocols\n");
        return;
    } 

    printf("Successfully connected to the server! Data received: %d\n", recv_data);
}


int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <ip of the host>\n", argv[0]);
        return -1;
    }
    struct sockaddr_in client_info = {0};
    client_info.sin_family  = AF_INET;
    client_info.sin_port = htons(PORT);
    client_info.sin_addr.s_addr = inet_addr(argv[1]);
    int client_socket = socket(AF_INET ,SOCK_STREAM,0);
    if(client_socket == -1){
        return -1;
    }
    int server_fd = connect(client_socket,  (struct sockaddr *) &client_info, sizeof(client_info));
    if(server_fd == -1){
        perror("Connect");
        return -1;
    }
    handle_server(client_socket);
    close(client_socket);
    return 0;
}
