#ifndef GENERAL_H
#define	GENERAL_H

#include <xc.h>

#define _XTAL_FREQ 48000000
#define MAX_LOOP_TIME_DIFF_ms 500

#define LED_1_LAT LATB1
#define LED_2_LAT LATB2

void uart_init(void);

void led_init(void);
void led_1_heartbeat(void);

#endif	/* GENERAL_H */

