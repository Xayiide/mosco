#include <string.h>    /* memcpy */
#include <arpa/inet.h> /* ntohs, etc. */

#include "pack.h"


u8 unpack_u8(const u8 **buf)
{
    u8 val;

    val = **buf;
    (*buf)++;

    return val;
}

u16 unpack_u16(const u8 **buf)
{
    u16 val;

    memcpy(&val, *buf, sizeof(u16));
    (*buf) += sizeof(u16);

    return ntohs(val);
}

u32 unpack_u32(const u8 **buf)
{
    u32 val;

    memcpy(&val, *buf, sizeof(u32));
    (*buf) += sizeof(u32);

    return ntohl(val);
}

u8 *unpack_bytes(const u8 **buf, size_t len, u8 *str)
{
    memcpy(str, *buf, len);
    str[len] = '\0';
    (*buf) += len;

    return str;
}

