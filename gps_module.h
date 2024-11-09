#ifndef GPS_H
#define	GPS_H

#include <stdint.h>

void gps_init(void);

void assemble_can_msgs(void);

void gps_handle_byte(uint8_t byte);


#endif	/* GPS_H */

