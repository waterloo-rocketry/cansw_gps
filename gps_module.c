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
static char timeStamp[9];
static int timeStampIndex;
static char latitude[10];
static int latitudeIndex;
static char latdir;
static char longitude[10];
static int longitudeIndex;
static char longdir;
static char qualind;
static char numOfSat[3];
static int numOfSatIndex;
static char HDOP[3];
static int HDOPIndex;
static char ANTALT[10];
static int ANTALTIndex;
static char ALTUNIT[2];
static int ALTUNITIndex;

static char GPGGA[5] = {'G', 'P', 'G', 'G', 'A'};   // hack
static enum PARSER_STATE state = P_IDLE;

void gps_handle_byte(uint8_t byte) {

    switch(byte) {
        case '$':
            state = P_MSG_TYPE;
            msgTypeIndex = 0;
            timeStampIndex = 0;
            latitudeIndex = 0;
            longitudeIndex = 0;
            numOfSatIndex = 0;
            HDOPIndex = 0;
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
                    timeStamp[timeStampIndex++] = byte;
                    break;
                case P_LATITUDE:
                    latitude[latitudeIndex++] = byte;
                    break;
                case P_LATITUDE_DIR_NS:
                    latdir = byte;
                    break;
                case P_LONGITUDE:
                    longitude[longitudeIndex++] = byte;
                    break;
                case P_LONGITUDE_DIR_EW:
                    longdir = byte;
                    break;
                case P_QUALITY:
                    qualind = byte;
                    break;
                case P_NUM_SATELLITES:
                    numOfSat[numOfSatIndex++] = byte;
                    break;
                case P_HDOP:
                    HDOP[HDOPIndex++] = byte;
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