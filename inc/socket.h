#define PORT 9000
#define BACKLOG 5
#define LOCALHOST 127.0.0.1
typedef enum{
    PROTO_HELLO,
}proto_type_e;

typedef struct{
    proto_type_e type;
    unsigned int length;
}proto_type_header_e;


