#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "timer.h"
#include <string.h>
#include "gps_module.h"
#include "gps_general.h"

#include <stdlib.h>
#include <string.h>

#include <xc.h>

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

// converts string to whole number plus 2 decimal places
void strtodec(char *str, int *whole, int *decimal) {
    char *endptr;
    *whole = strtol(str, &endptr, 10);
    if (endptr[0] == '.')
        *decimal = (int) (strtof(endptr, NULL) * 100);
    else
        *decimal = 0;
}

void assemble_can_msgs_utc(void) {
    can_msg_t msg_utc;

    int utc, dsec;
    strtodec(parser.msg, &utc, &dsec);

    build_gps_time_msg(millis(), utc / 10000, utc / 100 % 100, utc % 100, dsec, &msg_utc);
    txb_enqueue(&msg_utc);
}

void assemble_can_msgs_lat(void) {
    can_msg_t msg_lat;

    int lat, dmin;
    strtodec(parser.coord.msg, &lat, &dmin);

    build_gps_lat_msg(millis(), lat / 100, lat % 100, dmin, parser.coord.dir, &msg_lat);
    txb_enqueue(&msg_lat);
}

void assemble_can_msgs_lon(void) {
    can_msg_t msg_lon;

    int lon, dmin;
    strtodec(parser.coord.msg, &lon, &dmin);

    build_gps_lon_msg(millis(), lon / 100, lon % 100, dmin, parser.coord.dir, &msg_lon);
    txb_enqueue(&msg_lon);
}

void assemble_can_msgs_alt(void) {
    can_msg_t msg_alt;

    int alt, dalt;
    strtodec(parser.coord.msg, &alt, &dalt);

    build_gps_alt_msg(millis(), alt, dalt, parser.coord.dir, &msg_alt);
    txb_enqueue(&msg_alt);
}

void assemble_can_msgs_info(void) {
    can_msg_t msg_info;

    int numsat = strtol(parser.qual.numsat, NULL, 10);
    int quality = parser.qual.indicator - '0';

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
                case P_ERROR: // Error state
                    break;
                default: // Should be unreachable
                    // E_CODING_FUCKUP
                    break;
            }
        }
    }
}
