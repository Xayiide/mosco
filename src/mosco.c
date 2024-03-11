#include <stdio.h>

#include "mqtt.h"
#include "pack.h"

void encode_and_print(size_t len)
{
    uint8_t buf[4] = {0};
    i32     ret, i;

    ret = mqtt_encode_length(buf, len);

    printf("(%10d) ", (i32) len);
    printf("[%d] 0x", ret);
    for (i = 0; i < ret; i++)
        printf("%02X", buf[i]);
    printf("\n");
}

void encode_and_print_all()
{
    encode_and_print((size_t) 0);
    encode_and_print((size_t) 127);

    encode_and_print((size_t) 128);
    encode_and_print((size_t) 16383);

    encode_and_print((size_t) 16384);
    encode_and_print((size_t) 2097151);

    encode_and_print((size_t) 2097152);
    encode_and_print((size_t) 268435455);

    encode_and_print((size_t) 268435456);
}


void decode_and_print(u8 *buf)
{
    i32 ret;

    ret = mqtt_decode_length(buf);
    printf("[%d]\n", ret);
}

void decode_and_print_all()
{
    u8 b0[1]   = {0x00};
    u8 b127[1] = {0x7F};

    u8 b128[2]   = {0x80, 0x01};
    u8 b16383[2] = {0xFF, 0x7F};

    u8 b16384[3]   = {0x80, 0x80, 0x01};
    u8 b2097151[3] = {0xFF, 0xFF, 0x7F};

    u8 b2097152[4]   = {0x80, 0x80, 0x80, 0x01};
    u8 b268435455[4] = {0xFF, 0xFF, 0xFF, 0x7F};
    u8 b268435456[4] = {0xFF, 0xFF, 0xFF, 0xFF};

    decode_and_print(b0);
    decode_and_print(b127);
    decode_and_print(b128);
    decode_and_print(b16383);
    decode_and_print(b16384);
    decode_and_print(b2097151);
    decode_and_print(b2097152);
    decode_and_print(b268435455);
    decode_and_print(b268435456);
}


void unpack_u8_and_print(u8 *buf)
{
    u8  ret;
    i32 i;

    for (i = 0; i < 4; i++) {
        ret = unpack_u8((const u8 **) &buf);
        printf("ret: %d\n", ret);
    }
}

void unpack_u16_and_print(u8 *buf)
{
    u16 ret;
    u32 i;

    for (i = 0; i < 2; i++) {
        ret = unpack_u16((const u8 **) &buf);
        printf("ret: %d\n", ret);
    }
}


int main()
{
    encode_and_print_all();
    decode_and_print_all();

    
    u8 buf[4] = {0, 1, 2, 3};

    unpack_u8_and_print(buf);
    unpack_u16_and_print(buf);

    return 0;
}

