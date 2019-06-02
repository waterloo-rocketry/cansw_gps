#ifndef GPS_H
#define	GPS_H

#include <stdint.h>

// typedef struct gps_info {
    char msgType[5];
    int msgTypeIndex;
    char timeStamp[9];
    int timeStampIndex;
    char latitude[10];
    int latitudeIndex;
    char latdir;
    char longitude[10];
    int longitudeIndex;
    char longdir;
    char qualind;
    char numOfSat[3];
    int numOfSatIndex;
    char HDOP[3];
    int HDOPIndex;
    char ANTALT[10];
    int ANTALTIndex;
    char ALTUNIT[2];
    int ALTUNITIndex;

    // temp FIXME remove
    int x;

    char buffer[100];
    int y;
    char buffer1[100];
    int y1;
    char buffer2[100];
    int y2;
    char buffer3[100];
    int y3;
// } gps_info_t;

void gps_handle_byte(uint8_t byte);

#endif	/* GPS_H */

