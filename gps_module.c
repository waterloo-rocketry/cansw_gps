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

void gps_init(void) {
    //SET port C4 as output pin (WAKEUP) (This might not be needed during power_up, but I'll leave this here for reference later)
    TRISC4 = 0;

    //Set port C6 as output pin (RESET)
    TRISC6 = 0;

    //Set port C2 as output pin (ON_OFF)
    TRISC2 = 0;

    // Write a 1 to port C4 (WAKEUP)
    LATC4 = 1;

    //Toggle C2 for first startup after power on
    LATC2 = 1;
    __delay_ms(250);
    LATC2 = 0;

    // Write a 1 to port C6 (RESET) Writing a 1 because active low
    LATC6 = 1;
}

// message contents, stored locally
static char msgType[5];
static int msgTypeIndex;
static char timestamp[9];
static int timestamp_index;
static char latitude[10];
static int latitude_index;
static char latdir;
static char longitude[10];
static int longitude_index;
static char longdir;
static char qualind;
static char numsat[3];
static int numsat_index;
static char hdop[3];
static int hdop_index;
static char ANTALT[10];
static int ANTALTIndex;
static char ALTUNIT[2];
static int ALTUNITIndex;

static char GPGGA[5] = {'G', 'P', 'G', 'G', 'A'};   // hack
static enum PARSER_STATE state = P_IDLE;

// assuming we only pass it base 10 digits, which should be true for this
#define DIGIT(x) (x - '0')

static void assemble_can_msgs(void) {
    can_msg_t msg;

    // UTC format is hhmmss.ss
    uint8_t utc_hours = DIGIT(timestamp[0]) * 10 + DIGIT(timestamp[1]);
    uint8_t utc_mins = DIGIT(timestamp[2]) * 10 + DIGIT(timestamp[3]);
    uint8_t utc_secs = DIGIT(timestamp[4]) * 10 + DIGIT(timestamp[5]);
    // skip the period
    uint8_t utc_dsecs = DIGIT(timestamp[7]) * 10 + DIGIT(timestamp[8]);
    build_gps_time_msg(millis(), utc_hours, utc_mins, utc_secs, utc_dsecs, &msg);
    // copy message over to msg queue
    txb_enqueue(&msg);
}

void gps_handle_byte(uint8_t byte) {

    switch(byte) {
        case '$':
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
                   if ((msgType[0] == GPGGA[0]) && (msgType[1] == GPGGA[1])
                            && (msgType[2] == GPGGA[2]) && (msgType[3] == GPGGA[3])
                            && (msgType[4] == GPGGA[4])) {
                        //if we read a GPGGA signal, then the state machine carries on
                        state++;

                        // blink the LEDs
                        LATB1 ^= 1;
                        LATB2 ^= 1;
                        LATB3 ^= 1;
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
                    LATB3 ^= 1;
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
                    longdir = byte;
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
                    if (ALTUNITIndex == 3) {
                        state = P_STOP;
                    }
                    break;
                case P_STOP:    //STOP, wait for next
                    // FIXME: enqueue GPS message here
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