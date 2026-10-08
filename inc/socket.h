#ifndef SOCKET_CONFIG_H
#define SOCKET_CONFIG_H
#define SERVER_PORT 9000
#define CLIENT_PORT 9001
#define BACKLOG 5
#define LOCALHOST 127.0.0.1
#define MESSAGE_BUFFER_SIZE 100
typedef enum{
    PROTO_HELLO,
}proto_type_e;

typedef struct{
    proto_type_e type;
    unsigned int length;
}proto_type_header_e;

#endif
