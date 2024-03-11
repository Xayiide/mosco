#include "include/types.h"
#include "include/mqtt.h"

#include <stddef.h> /* size_t */

/* Longitud máxima que puede tener el campo Remaining
 * Length en bytes.
 */
static const int MAX_LEN_BYTES = 4;


i32 mqtt_encode_length(u8 *buf, size_t len)
{
    i32    bytes = 0;
    size_t encoded_byte;

    do {
        if (bytes + 1> MAX_LEN_BYTES)
            return bytes;
        encoded_byte = len % 128;
        len          = len / 128;
        if (len > 0)
            encoded_byte |= 128;
        buf[bytes] = encoded_byte;
        bytes++;
    } while (len > 0);

    return bytes;
}
