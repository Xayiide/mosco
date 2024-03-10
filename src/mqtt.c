#include "include/types.h"
#include "include/mqtt.h"

#include <stddef.h> /* size_t */

/* Longitud máxima que puede tener el campo Remaining
 * Length en bytes.
 */
static const int MAX_LEN_BYTES = 4;


i32 mqtt_encode_length(u8 *buf, size_t len)
{

}
