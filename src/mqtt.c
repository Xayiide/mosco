#include "include/types.h"
#include "include/mqtt.h"

#include <stddef.h> /* size_t */

/* Longitud máxima que puede tener el campo Remaining
 * Length en bytes.
 */
static const int MAX_LEN_BYTES = 4;


/* Guarda en buf el valor de len codificado. Devuelve el nº de bytes usados */
i32 mqtt_encode_length(u8 *buf, size_t len)
{
    i32 nbytes = 0;
    u8  encoded_byte;

    do {
        if (nbytes + 1 > MAX_LEN_BYTES)
            return nbytes;
        encoded_byte = len % 128;
        len          = len / 128;
        if (len > 0)
            encoded_byte |= 128;
        buf[nbytes] = encoded_byte;
        nbytes++;
    } while (len > 0);

    return nbytes;
}

/* Devuelve el valor de buf decodificado, o -1 si ocurre un error */
i32 mqtt_decode_length(u8 *buf)
{
    i32 multiplier = 1;
    i32 value      = 0;
    u8  pos        = 0;
    u8  encoded_byte;

    do {
        encoded_byte = buf[pos];
        pos++;
        value += (encoded_byte & 127) * multiplier;
        if (multiplier > 128 * 128 * 128)
            return -1;
        multiplier *= 128;
    } while ((encoded_byte & 128) != 0);

    return value;
}
