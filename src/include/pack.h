#ifndef PACK_H_
#define PACK_H_

#include "types.h"

u8  unpack_u8(const u8 **buf);
u16 unpack_u16(const u8 **buf);
u32 unpack_u32(const u8 **buf);
u8 *unpack_bytes(const u8 **buf, size_t len, u8 *str);

#endif
