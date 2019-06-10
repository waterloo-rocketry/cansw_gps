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

#include <xc.h>

void gps_init(void) {
    //SET port C4 as output pin (WAKEUP) (This might not be needed during power_up, but I'll leave this here for reference later)
    TRISC4 = 0;

    //Set port C6 as output pin (RESET)
    TRISC6 = 0;

    //Set port C2 as output pin (ON_OFF)
    TRISC2 = 0;

    // Write a 1 to port C4 (WAKEUP)
    LATC4 = 1;
    LATC2 = 0;
    //Toggle C2 for first startup after power on
    LATC2 = 1;
    __delay_ms(300);
    LATC2 = 0;
    __delay_ms(300);
    for (int x = 0; x < 100; x++) {
       //LATC2 = 1; 
       __delay_ms(10);
    }
    
    // Write a 1 to port C6 (RESET) Writing a 1 because active low
    LATC6 = 1;
}

// message contents, stored locally
//I've commented out the placeholders that I've been using
static char msgType[5];
static int msgTypeIndex;
static char timestamp[9];
static int timestamp_index;
static char latitude[10];
static int latitude_index;
static char latdir;
static char longitude[10];
static int longitude_index;
static char londir;
static char qualind = 0;
static char numsat[3];
static int numsat_index;
static char hdop[3];
static int hdop_index;
static char ANTALT[10];
static int ANTALTIndex;
static char ALTUNIT[2];
static int ALTUNITIndex;

static enum PARSER_STATE state = P_IDLE;

// assuming we only pass it base 10 digits, which should be true for this
#define DIGIT(x) (x - '0')

void assemble_can_msgs_utc(void) {
    can_msg_t msg_utc;

    // UTC format is hhmmss.ss
    uint8_t utc_hours = DIGIT(timestamp[0]) * 10 + DIGIT(timestamp[1]);
    uint8_t utc_mins = DIGIT(timestamp[2]) * 10 + DIGIT(timestamp[3]);
    uint8_t utc_secs = DIGIT(timestamp[4]) * 10 + DIGIT(timestamp[5]);
    // skip the period
    uint8_t utc_dsecs = DIGIT(timestamp[7]) * 10 + DIGIT(timestamp[8]);
    build_gps_time_msg(millis(), utc_hours, utc_mins, utc_secs, utc_dsecs, &msg_utc);
    // copy message over to msg queue
    txb_enqueue(&msg_utc);
}

void assemble_can_msgs_lat(void) {
    can_msg_t msg_lat;
    
    // Latitude format is DDMM.MM (we ignore only take the first 2 decimals)
    uint8_t lat_degree = DIGIT(latitude[0]) * 10 + DIGIT(latitude[1]);
    uint8_t lat_minute = DIGIT(latitude[2]) * 10 + DIGIT(latitude[3]);
    // We skip over the decimal point here
    uint8_t lat_dminutes = DIGIT(latitude[5]) * 10 + DIGIT(latitude[6]);
    build_gps_lat_msg(millis(), lat_degree, lat_minute, lat_dminutes, latdir, &msg_lat);
    txb_enqueue(&msg_lat);
}

void assemble_can_msgs_lon(void) {
    can_msg_t msg_lon;
    
    // Longitude format is DDDMM.MM (we ignore only take the first 2 decimals)
    uint8_t lon_degree = DIGIT(longitude[0]) * 100 + DIGIT(longitude[1]) * 10 + DIGIT(longitude[2]);
    uint8_t lon_minute = DIGIT(longitude[3]) * 10 + DIGIT(longitude[4]);
    // We skip over the decimal point here
    uint8_t lon_dminutes = DIGIT(longitude[6]) * 10 + DIGIT(longitude[7]);
    build_gps_lon_msg(millis(), lon_degree, lon_minute, lon_dminutes, londir, &msg_lon);
    txb_enqueue(&msg_lon);
}    

void assemble_can_msgs_alt(void) {
    can_msg_t msg_alt;
    // Altitude format can either be AAA.D or AAAA.D depending on how high we are. Thus, we need to find the decimal position.
    uint8_t decimal_place= 0;
    for (int x = 0; x < 10; x++) {
        if (ANTALT[x] == '.') {
            decimal_place = x;
        }
    }
    // Decimal_place can be either 3 or 4 (eg altitude < 1000m for 3 or <10000m for 4.
    // We shouldn't reach 5, and we definitely won't hit 2)
    if (decimal_place == 3) {
        uint16_t altitude = DIGIT(ANTALT[0]) * 100 + DIGIT(ANTALT[1]) * 10 + DIGIT(ANTALT[2]);
        uint8_t daltitude = DIGIT(ANTALT[4]);
        build_gps_alt_msg(millis(), altitude, daltitude, ALTUNIT[0], &msg_alt);
        txb_enqueue(&msg_alt);
    } else if (decimal_place == 4) {
        uint16_t altitude = DIGIT(ANTALT[0]) * 1000 + DIGIT(ANTALT[1]) * 100 + DIGIT(ANTALT[2]) * 10 + DIGIT(ANTALT[3]);
        uint8_t daltitude = DIGIT(ANTALT[5]);
        build_gps_alt_msg(millis(), altitude, daltitude, ALTUNIT[0], &msg_alt);
        txb_enqueue(&msg_alt);
    }
}
    
void assemble_can_msgs_info(void) {
    can_msg_t msg_info;
    // Info format is currently number of satellites + quality
    uint8_t num_sat = DIGIT(numsat[0]) * 10 + DIGIT(numsat[1]);
    uint8_t quality = DIGIT(qualind);
    build_gps_info_msg(millis(), num_sat, quality, &msg_info);
    txb_enqueue(&msg_info);
}

void gps_handle_byte(uint8_t byte) {
    switch(byte) {
        case '$':
            LATB2 ^= 1;
            state = P_MSG_TYPE;
            msgTypeIndex = 0;
            timestamp_index = 0;
            latitude_index = 0;
            longitude_index = 0;
            numsat_index = 0;
            hdop_index = 0;
            ANTALTIndex = 0;
            ALTUNITIndex = 0;
            break;

        case ',':
            if (P_MSG_TYPE <= state && state < P_ERROR) {
                   // apparently strcmp is being annoying
                   if ((msgType[0] == 'G') && (msgType[1] == 'P')
                            && (msgType[2] == 'G') && (msgType[3] == 'G')
                            && (msgType[4] == 'A')) {
                        //if we read a GPGGA signal, then the state machine carries on
                        if (state == P_TIMESTAMP && *(timestamp) !=0 && *(latitude) != 0 && *(longitude) != 0 && qualind != 0 && *(ANTALT) != 0) {
                            assemble_can_msgs_utc();
                        } else if (state == P_LATITUDE_DIR_NS && *(latitude) != 0) {
                            assemble_can_msgs_lat();
                        } else if (state == P_LONGITUDE_DIR_EW && *(longitude) != 0) {
                            assemble_can_msgs_lon();
                        } else if (state == P_NUM_SATELLITES && qualind != 0) {
                            //assemble_can_msgs_info();
                        } else if (state == P_ALTITUDE_UNITS && *(ANTALT) != 0) {
                            assemble_can_msgs_alt();
                        }
                        state++;
                   } else {
                        //if we don't read a GPGGA signal, then we wont care about the message for now
                        state = P_IDLE;
                   }
            }
            break;

        // Parse message fields
        default: {
            switch(state) {
                case P_IDLE:    //idle do nothing
                    break;
                case P_START:   //start, for debugging purposes
                    // FIXME: begin new GPS message here
                    break;
                case P_MSG_TYPE:
                    msgType[msgTypeIndex++] = byte;
                    break;
                case P_TIMESTAMP:
                    timestamp[timestamp_index++] = byte;
                    break;
                case P_LATITUDE:
                    latitude[latitude_index++] = byte;
                    break;
                case P_LATITUDE_DIR_NS:
                    latdir = byte;
                    break;
                case P_LONGITUDE:
                    longitude[longitude_index++] = byte;
                    break;
                case P_LONGITUDE_DIR_EW:
                    londir = byte;
                    break;
                case P_QUALITY:
                    qualind = byte;
                    break;
                case P_NUM_SATELLITES:
                    numsat[numsat_index++] = byte;
                    break;
                case P_HDOP:
                    hdop[hdop_index++] = byte;
                    break;
                case P_ALTITUDE_ANTENNA:
                    ANTALT[ANTALTIndex++] = byte;
                    break;
                case P_ALTITUDE_UNITS:
                    ALTUNIT[ALTUNITIndex++] = byte;
                    break;
                case P_STOP:    //STOP, wait for next
                    LATB3 ^= 1;
                    state = P_IDLE;
                    break;
                case P_ERROR:   //ERROR state
                    break;
                default:        // Should be unreachable
                    // E_CODING_FUCKUP
                    break;
            }
        }
    }
}