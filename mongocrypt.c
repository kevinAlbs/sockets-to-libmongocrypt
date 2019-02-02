#include "mongocrypt.h"

#include <ctype.h>
#include <stdio.h>

/* The bytes for an ismaster command (courtesy of wireshark). */
static uint8_t ismaster_bytes[] = {0x3a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x01, 0x69, 0x73, 0x4d, 0x61, 0x73, 0x74, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x02, 0x24, 0x64, 0x62, 0x00, 0x05, 0x00, 0x00, 0x00, 0x74, 0x65, 0x73, 0x74, 0x00, 0x00};

void mongocrypt_encrypt(mongocrypt_stream_t *mongod_stream)
{
    uint8_t buf[1024];
    uint32_t *msg_len;
    uint32_t i;

    /* Use the stream provided by Python to send an 'ismaster' and receive the response. */
    mongod_stream->send(mongod_stream->ctx, ismaster_bytes, sizeof(ismaster_bytes));
    mongod_stream->recv(mongod_stream->ctx, 4, buf);
    msg_len = (uint32_t *)buf;
    mongod_stream->recv(mongod_stream->ctx, (*msg_len) - 4, buf + 4);

    printf("ismaster response:\n");
    /* Print out readable bits. */
    for (i = 0; i < *msg_len; i++)
    {
        printf("%c", isalpha(buf[i]) ? buf[i] : '.');
    }
    printf("\n");
}
