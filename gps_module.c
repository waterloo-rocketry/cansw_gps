#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "timer.h"
#include "gps_module.h"
#include "gps_general.h"

#include <xc.h>
#include <string.h>

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

// message contents, stored locally
//I've commented out the placeholders that I've been using
static union {
    char msg[10];
    struct {
        char msg[10];
        char dir;
    } coord;
    struct {
        char indicator;
        char numsat[2];
    } qual;
} parser;
size_t parser_index = 0;

static enum PARSER_STATE state = P_IDLE;

// converts string to whole number plus 4 decimal places
void strtodec(char *str, size_t len, uint32_t *whole, uint16_t *decimal) {

    uint16_t decimal_place = 1000;

    *whole = 0;
    *decimal = 0;

    char *current = str;
    while(current < str + len && '0' <= *current && '9' >= *current) {
        *whole = *whole*10 + (*current - '0');
        current++;
    }

    if(current >= str + len || *current != '.')
        return;

    current++;

    while(decimal_place > 0 && current < str + len && '0' <= *current && '9' >= *current) {
        *decimal += decimal_place * (*current - '0');
        decimal_place /= 10;
        current++;
    }
}

void assemble_can_msgs_utc(void) {
    can_msg_t msg_utc;

    uint32_t utc;
    uint16_t dsec;
    strtodec(parser.msg, 10, &utc, &dsec);

    build_gps_time_msg(millis(), (uint8_t) (utc / 10000 % 100), (uint8_t) (utc / 100 % 100), (uint8_t) (utc % 100), (uint8_t) (dsec / 100), &msg_utc);
    txb_enqueue(&msg_utc);
}

void assemble_can_msgs_lat(void) {
    can_msg_t msg_lat;

    uint32_t lat;
    uint16_t dmin;
    strtodec(parser.coord.msg, 10, &lat, &dmin);

    build_gps_lat_msg(millis(), (uint8_t) (lat / 100), (uint8_t) (lat % 100), (uint16_t) dmin, parser.coord.dir, &msg_lat);
    txb_enqueue(&msg_lat);
}

void assemble_can_msgs_lon(void) {
    can_msg_t msg_lon;

    uint32_t lon;
    uint16_t dmin;
    strtodec(parser.coord.msg, 10, &lon, &dmin);

    build_gps_lon_msg(millis(), (uint8_t) (lon / 100), (uint8_t) (lon % 100), (uint16_t) dmin, parser.coord.dir, &msg_lon);
    txb_enqueue(&msg_lon);
}

void assemble_can_msgs_alt(void) {
    can_msg_t msg_alt;

    uint32_t alt;
    uint16_t dalt;
    strtodec(parser.coord.msg, 10, &alt, &dalt);

    build_gps_alt_msg(millis(), (uint16_t) alt, (uint8_t) (dalt / 100), parser.coord.dir, &msg_alt);
    txb_enqueue(&msg_alt);
}

void assemble_can_msgs_info(void) {
    can_msg_t msg_info;

    uint8_t numsat = (uint8_t) strtol(parser.qual.numsat, NULL, 10);
    uint8_t quality = parser.qual.indicator - '0';

    build_gps_info_msg(millis(), numsat, quality, &msg_info);
    txb_enqueue(&msg_info);
}

void reset_parser() {
    parser_index = 0;
    memset(&parser, 0, sizeof(parser));
}

void gps_handle_byte(uint8_t byte) {

    switch(byte) {
        case '$':
            // Start of message
            state = P_MSG_TYPE;
            reset_parser();
            break;

        case ',':
            switch (state) {
                case P_IDLE:
                    // Not doing anything
                    return;
                case P_MSG_TYPE:
                    if (strncmp(parser.msg, "GPGGA", 5) != 0) {
                        // Not a GPGGA signal, then we don't care
                        state = P_STOP;
                        return;
                    } else {
                        LED_2_ON();
                    }
                    break;
                case P_TIMESTAMP:
                    if (parser.msg[0])
                        assemble_can_msgs_utc();
                    break;
                case P_LATITUDE_DIR_NS:
                    if (parser.coord.msg[0] && parser.coord.dir)
                        assemble_can_msgs_lat();
                    break;
                case P_LONGITUDE_DIR_EW:
                    if (parser.coord.msg[0] && parser.coord.dir)
                        assemble_can_msgs_lon();
                    break;
                case P_NUM_SATELLITES:
                    if (parser.qual.indicator && parser.qual.numsat[0])
                        assemble_can_msgs_info();
                    break;
                case P_ALTITUDE_UNITS:
                    if (parser.coord.msg[0] && parser.coord.dir)
                        assemble_can_msgs_alt();
                    break;
                default:
                    // Don't have full message yet, don't reset parser
                    state++;
                    return;
            }

            reset_parser();
            state++;

            break;

        // Parse message fields
        default: {
            switch(state) {
                case P_IDLE:
                    break;
                case P_MSG_TYPE:
                case P_TIMESTAMP:
                    if (parser_index < sizeof(parser.msg))
                        parser.msg[parser_index++] = byte;
                    break;
                case P_LATITUDE:
                case P_LONGITUDE:
                    if (parser_index < sizeof(parser.coord.msg))
                        parser.coord.msg[parser_index++] = byte;
                    break;
                case P_LATITUDE_DIR_NS:
                case P_LONGITUDE_DIR_EW:
                    parser.coord.dir = byte;
                    break;
                case P_QUALITY:
                    parser.qual.indicator = byte;
                    break;
                case P_NUM_SATELLITES:
                    if (parser_index < sizeof(parser.qual.numsat))
                        parser.qual.numsat[parser_index++] = byte;
                    break;
                case P_HDOP:
                    break;
                case P_ALTITUDE_ANTENNA:
                    if (parser_index < sizeof(parser.coord.msg))
                        parser.coord.msg[parser_index++] = byte;
                    break;
                case P_ALTITUDE_UNITS:
                    parser.coord.dir = byte;
                    break;
                case P_STOP:
                    LED_2_OFF();
                    state = P_IDLE;
                    break;
                default: // Should be unreachable
                    // E_CODING_FUCKUP
                    LED_2_OFF();
                    state = P_IDLE;
                    break;
            }
        }
    }
}
