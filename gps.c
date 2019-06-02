#include "gps.h"
#include <xc.h>

// Order matters for this enum
enum PARSER_STATE {
    P_IDLE = 0,
    P_START,
    P_MSG_TYPE,
    P_TIMESTAMP,
    P_LATITUDE,
    P_LATITUDE_DIR_NS,
    P_LONGITUDE,
    P_LONGITUDE_DIR_EW,
    P_QUALITY,            // Quality Indicator:
                        // 1 = Uncorrected coordinate
                        // 2 = Differentially correct coordinate (e.g., WAAS, DGPS)
                        // 4 = RTK Fix coordinate (centimeter precision)
                        // 5 = RTK Float (decimeter precision.
    P_NUM_SATELLITES,
    P_HDOP,               // (horizontal dilution of precision)
    P_ALTITUDE_ANTENNA,
    P_ALTITUDE_UNITS,
    P_STOP,
    P_ERROR,
};
static enum PARSER_STATE state = P_IDLE;

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