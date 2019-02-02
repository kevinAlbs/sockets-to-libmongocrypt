#include <stdint.h>

typedef void (*send_fn)(void* ctx, const uint8_t* in, int to_send);
typedef void (*recv_fn)(void* ctx, int to_recv, uint8_t* out);

typedef struct {
    send_fn send;
    recv_fn recv;
    int x;
    void* ctx;
} mongocrypt_stream_t;

void mongocrypt_encrypt (mongocrypt_stream_t* mongod_stream);