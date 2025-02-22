#include <string.h>

#include <xc.h>

#include "canlib.h"
#include "timer.h"

#include "gps_general.h"
#include "gps_module.h"

// Order matters for this enum, matches the order of GPGGA fields
typedef enum {
    P_IDLE = 0,
    P_MSG_TYPE,
    P_TIMESTAMP,
    P_LATITUDE,
    P_LATITUDE_DIR_NS,
    P_LONGITUDE,
    P_LONGITUDE_DIR_EW,
    P_QUALITY, // Quality Indicator:
               // 1 = Uncorrected coordinate
               // 2 = Differentially correct coordinate (e.g., WAAS, DGPS)
               // 4 = RTK Fix coordinate (centimeter precision)
               // 5 = RTK Float (decimeter precision.
               // 6 = Dead reckoning mode
    P_NUM_SATELLITES,
    P_HDOP, // horizontal dilution of precision
    P_ALTITUDE,
    P_ALTITUDE_UNITS,
    P_UNDULATION, // geoid-to-ellipsoid separation
    P_UNDULATION_UNITS,
    P_AGE,
    P_DIFF_REF_ID,
    P_CHECKSUM,
    P_STOP,
} parser_state;

typedef struct {
    char msg[10];
    char dir;
} parser_coord;

typedef struct {
    char indicator;
    char numsat[2];
} parser_qual;

static struct {
    parser_state state;
    uint8_t checksum;
    size_t index;
    char msg_type[5];
    char utc[10];
    parser_coord lat;
    parser_coord lon;
    parser_qual qual;
    parser_coord alt;
    char exp_checksum[2];
} parser;

void gps_init(void) {
    // Set port C2 as output pin (~HWR)
    TRISC2 = 0;

    // Set C2 to high because it's active low
    LATC2 = 1;

    // Set C3 to input (FIX)
    TRISC3 = 1;

    // Set C4 to input (PPS)
    TRISC4 = 1;
}

// converts string to whole number plus 4 decimal places
void strtodec(char *str, size_t len, uint32_t *whole, uint16_t *decimal) {
    uint16_t decimal_place = 1000;

    *whole = 0;
    *decimal = 0;

    char *current = str;
    while (current < str + len && '0' <= *current && '9' >= *current) {
        *whole = *whole * 10 + (*current - '0');
        current++;
    }

    if (current >= str + len || *current != '.') {
        return;
    }

    current++;

    while (decimal_place > 0 && current < str + len && '0' <= *current && '9' >= *current) {
        *decimal += decimal_place * (*current - '0');
        decimal_place /= 10;
        current++;
    }
}

// converts a hex char to integer
uint8_t hextoint(char hex) {
    if ('0' <= hex && hex <= '9') {
        return hex - '0';
    }
    if ('a' <= hex && hex <= 'f') {
        return hex - 'a' + 10;
    }
    if ('A' <= hex && hex <= 'F') {
        return hex - 'A' + 10;
    }
    return 0;
}

void enqueue_can_msgs_utc(uint32_t timestamp) {
    can_msg_t msg_utc;

    uint32_t utc;
    uint16_t dsec;
    strtodec(parser.utc, 10, &utc, &dsec);

    // message format: hhmmss.sss
    // strtodec returns 4 digits for dsec, so we divide it by 100 to make it fit within a byte.
    build_gps_time_msg(
        PRIO_HIGH,
        timestamp,
        (uint8_t)(utc / 10000 % 100),
        (uint8_t)(utc / 100 % 100),
        (uint8_t)(utc % 100),
        (uint8_t)(dsec / 100),
        &msg_utc
    );
    txb_enqueue(&msg_utc);
}

void enqueue_can_msgs_lat(uint32_t timestamp) {
    can_msg_t msg_lat;

    uint32_t lat;
    uint16_t dmin;
    strtodec(parser.lat.msg, 10, &lat, &dmin);

    // messge format: ddmm.mmmm
    build_gps_lat_msg(
        PRIO_HIGH,
        timestamp,
        (uint8_t)(lat / 100),
        (uint8_t)(lat % 100),
        (uint16_t)dmin,
        parser.lat.dir,
        &msg_lat
    );
    txb_enqueue(&msg_lat);
}

void enqueue_can_msgs_lon(uint32_t timestamp) {
    can_msg_t msg_lon;

    uint32_t lon;
    uint16_t dmin;
    strtodec(parser.lon.msg, 10, &lon, &dmin);

    // message format: dddmm.mmmm
    build_gps_lon_msg(
        PRIO_HIGH,
        timestamp,
        (uint8_t)(lon / 100),
        (uint8_t)(lon % 100),
        (uint16_t)dmin,
        parser.lon.dir,
        &msg_lon
    );
    txb_enqueue(&msg_lon);
}

void enqueue_can_msgs_alt(uint32_t timestamp) {
    can_msg_t msg_alt;

    uint32_t alt;
    uint16_t dalt;
    strtodec(parser.alt.msg, 10, &alt, &dalt);

    // message format: just a normal decimal number, we divide decimal part by 100 to make it fit
    // within a byte
    build_gps_alt_msg(
        PRIO_HIGH, millis(), (uint16_t)alt, (uint8_t)(dalt / 100), parser.alt.dir, &msg_alt
    );
    txb_enqueue(&msg_alt);
}

void enqueue_can_msgs_info(uint32_t timestamp) {
    can_msg_t msg_info;

    uint8_t numsat = (uint8_t)strtol(parser.qual.numsat, NULL, 10);
    uint8_t quality = parser.qual.indicator - '0';

    build_gps_info_msg(PRIO_HIGH, timestamp, numsat, quality, &msg_info);
    txb_enqueue(&msg_info);
}

void reset_parser(void) {
    memset(&parser, 0, sizeof(parser));
}

void gps_handle_byte(uint8_t byte) {
    switch (byte) {
        case '$':
            // Start of message
            reset_parser();
            parser.state = P_MSG_TYPE;
            break;

        case ',':
            // Field separater
            if (parser.state == P_IDLE) {
                break;
            }
            if (parser.state == P_MSG_TYPE) {
                if (strncmp(parser.msg_type, "GPGGA", 5) != 0) {
                    // Not a GPGGA signal, then we don't care
                    parser.state = P_STOP;
                    return;
                } else {
                    LED_2_ON();
                }
            }

            parser.state++;
            parser.index = 0;
            parser.checksum ^= byte;

            break;

        case '*':
            // Checksum indicator
            if (parser.state == P_IDLE) {
                break;
            }
            parser.state = P_CHECKSUM;
            parser.index = 0;
            break;

        case '\r':
        case '\n': {
            // End of message
            if (parser.state == P_CHECKSUM) {
                uint8_t exp_checksum =
                    (hextoint(parser.exp_checksum[0]) << 4) | hextoint(parser.exp_checksum[1]);
                if (parser.checksum == exp_checksum) {
                    uint32_t timestamp = millis();
                    enqueue_can_msgs_utc(timestamp);
                    enqueue_can_msgs_lat(timestamp);
                    enqueue_can_msgs_lon(timestamp);
                    enqueue_can_msgs_info(timestamp);
                    enqueue_can_msgs_alt(timestamp);
                }
            }

            parser.state = P_STOP;
            break;
        }

        default: {
// help macro to safely add byte to parser message
#define APPEND_PARSER_MESSAGE(msg, byte)                                                           \
    do {                                                                                           \
        if (parser.index < sizeof(msg))                                                            \
            msg[parser.index++] = byte;                                                            \
    } while (0)

            // Parse message fields
            switch (parser.state) {
                case P_IDLE:
                    break;
                case P_MSG_TYPE:
                    APPEND_PARSER_MESSAGE(parser.msg_type, byte);
                    break;
                case P_TIMESTAMP:
                    APPEND_PARSER_MESSAGE(parser.utc, byte);
                    break;
                case P_LATITUDE:
                    APPEND_PARSER_MESSAGE(parser.lat.msg, byte);
                    break;
                case P_LONGITUDE:
                    APPEND_PARSER_MESSAGE(parser.lon.msg, byte);
                    break;
                case P_LATITUDE_DIR_NS:
                    parser.lat.dir = byte;
                    break;
                case P_LONGITUDE_DIR_EW:
                    parser.lon.dir = byte;
                    break;
                case P_QUALITY:
                    parser.qual.indicator = byte;
                    break;
                case P_NUM_SATELLITES:
                    APPEND_PARSER_MESSAGE(parser.qual.numsat, byte);
                    break;
                case P_HDOP:
                    break;
                case P_ALTITUDE:
                    APPEND_PARSER_MESSAGE(parser.alt.msg, byte);
                    break;
                case P_ALTITUDE_UNITS:
                    parser.alt.dir = byte;
                    break;
                case P_UNDULATION:
                case P_UNDULATION_UNITS:
                case P_AGE:
                case P_DIFF_REF_ID:
                    break;
                case P_CHECKSUM:
                    APPEND_PARSER_MESSAGE(parser.exp_checksum, byte);
                    break;
                case P_STOP:
                default:
                    LED_2_OFF();
                    parser.state = P_IDLE;
                    break;
            }

            if (parser.state != P_CHECKSUM) {
                parser.checksum ^= byte;
            }

            break;
        }
    }
}
