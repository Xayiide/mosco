#include <stdio.h>
#include "mqtt.h"

int main()
{
    uint8_t buf[4] = {0};
    int32_t res;

    (void) mqtt_encode_length(buf, 268435455);

    for (int i = 0; i < 4; i++) {
        printf("0x%X ", buf[i]);
    }

    printf("Mosco\n");
    return 0;
}

