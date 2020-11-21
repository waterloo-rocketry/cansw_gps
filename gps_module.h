#ifndef GPS_H
#define	GPS_H

#include <stdint.h>

// Order matters for this enum, matches the order of GPGGA fields
enum PARSER_STATE {
    P_IDLE = 0,
    P_MSG_TYPE,
    P_TIMESTAMP,
    P_LATITUDE,
    P_LATITUDE_DIR_NS,
    P_LONGITUDE,
    P_LONGITUDE_DIR_EW,
    P_QUALITY,          // Quality Indicator:
                        // 1 = Uncorrected coordinate
                        // 2 = Differentially correct coordinate (e.g., WAAS, DGPS)
                        // 4 = RTK Fix coordinate (centimeter precision)
                        // 5 = RTK Float (decimeter precision.
                        // 6 = Dead reckoning mode
    P_NUM_SATELLITES,
    P_HDOP,             // horizontal dilution of precision
    P_ALTITUDE_ANTENNA,
    P_ALTITUDE_UNITS,
    P_STOP,
};

void gps_init(void);

void assemble_can_msgs(void);

void gps_handle_byte(uint8_t byte);


#endif	/* GPS_H */

