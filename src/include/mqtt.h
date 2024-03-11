#ifndef MQTT_H_
#define MQTT_H_

#include "types.h"
#include <stdlib.h>

enum mqtt_control_packet_type
{
    CONNECT    = 1,
    CONNACK    = 2,
    PUBLISH    = 3,
    PUBACK     = 4,
    PUBREC     = 5,
    PUBREL     = 6,
    PUBCOMP    = 7,
    SUBSCRIBE  = 8,
    SUBACK     = 9,
    UNSUSCRIBE = 10,
    UNSUBACK   = 11,
    PINGREQ    = 12,
    PINGRESP   = 13,
    DISCONNECT = 14
};

/* Cabecera fija (2-5 B)
 * · Byte 1: 4 bits tipo + 4 bits reservados (flags)
 * · Byte 2-5: Longitud restante
 */
union mqtt_header
{
    u8 byte;
    struct {
        u8 retain : 1;
        u8 qos    : 2;
        u8 dup    : 1;
        u8 type   : 4;
    } bits;
};

/* - Cabecera fija
 * - Cabecera variable (10 B)
 *   · Protocol name (6 B):  2 long + MQTT
 *   · Protocol level (1 B): Valor: 4
 *   · Flags (1 B)
 *   · Keepalive (2 B)
 * - Datos:
 *   · Id cliente
 *   · Will topic
 *   · Will msg
 *   · Username
 *   · Password
 */
struct mqtt_connect {
    union {
        u8 byte;
        struct {
            u8 reserved      : 1;
            u8 clean_session : 1;
            u8 will          : 1;
            u8 will_qos      : 2;
            u8 will_retain   : 1;
            u8 password      : 1;
            u8 username      : 1;
        } bits;
    }; /* Flags */
    u16 keepalive;
    struct {
        u8  *client_id;
        u8  *username;
        u8  *password;
        u8  *will_topic;
        u8  *will_message;
    } payload;
};

/* - Cabecera fija
 * - Cabecera variable (2 B)
 *   · Flags (1 B): 7 bits a 0 + 1 bit Session Present
 *   · Return code (1 B)
 */
struct mqtt_connack {
    union {
        u8 byte;
        struct {
            u8 session_present : 1;
            u8 reserved        : 7;
        } bits;
    }; /* Flags */
    u8 rc;  /* return code */
};

/* - Cabecera fija
 * - Cabecera variable
 *   · Topic Name
 *   · Packet Id (2 B)
 * - Datos (los datos que sean)
 */
struct mqtt_pub {
    u16  topic_len;
    u8  *topic;
    u16  data_len;
    u8  *data;
};

/* - Cabecera fija
 * - Cabecera variable (2 B)
 *   · Packet identifier (2 B)
 * - Datos
 *   · Topic 1
 *     · Longitud del nombre del topic (2 B)
 *     · Nombre del topic (N Bytes)
 *     · Requested QoS (1 B: 6 bytes a 0 y 2 de QoS)
 *   · Topic 2 ...
 */
struct mqtt_sub {
    u16 pkt_id;
    u16 tuples_len;
    struct {
        u16  topic_len;
        u8  *topic;
        u8   qos;
    } *tuples;
};

/* - Cabecera fija
 * - Cabecera variable (2 B)
 *   · Packet id (2 B)
 * - Datos
 *   · Lista de RCs: 1 RC de 1 B por TF del SUB
 */
struct mqtt_suback {
    u16  packet_id;
    u16  rcs_len;
    u8  *rcs;
};

/* - Cabecera fija
 * - Cabecera variable (2 B)
 *   · Packet id (2 B)
 * - Datos
 *   · Topic 1
 *     · Longitud del nombre del topic (2 B)
 *     · Nombre del topic (N Bytes)
 *   · Topic 2 ...
 */
struct mqtt_unsub {
    u16 packet_id;
    u16 tuples_len;
    struct {
        u16  topic_len;
        u8  *topic;
    } *tuples;
};

struct mqtt_ack {
    u16 packet_id;
};

/* PUBACK, PUBREC, PUBREL, PUBCOMP y UNSUBACK son iguales */
typedef struct mqtt_ack mqtt_puback;
typedef struct mqtt_ack mqtt_pubrec;
typedef struct mqtt_ack mqtt_pubrel;
typedef struct mqtt_ack mqtt_pubcomp;
typedef struct mqtt_ack mqtt_unsuback;

typedef union mqtt_header mqtt_pingreq;
typedef union mqtt_header mqtt_pingresp;
typedef union mqtt_header mqtt_disconnect;

struct mqtt_packet {
    union mqtt_header header;
    union {
        struct mqtt_ack ack; /* Todos los ACKs menos el CONNACK */
        mqtt_pingreq ping;   /* pingreq, pingresp, disconnect */
        struct mqtt_connect connect;
        struct mqtt_connack connack;
        struct mqtt_pub     pub;
        struct mqtt_sub     sub;
        struct mqtt_suback  suback;
        struct mqtt_unsub   unsub;
    };
};

i32 mqtt_encode_length(u8 *buf, size_t len);

i32 mqtt_decode_length(u8 *buf);

#endif /* MQTT_H_ */
