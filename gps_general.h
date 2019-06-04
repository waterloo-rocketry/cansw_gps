#ifndef GENERAL_H
#define	GENERAL_H

#include <xc.h>

#define _XTAL_FREQ 1000000

#define LED_1_ON() (LATB1 = 0)
#define LED_1_OFF() (LATB1 = 1)
#define LED_2_ON() (LATB2 = 0)
#define LED_2_OFF() (LATB2 = 1)
#define LED_3_ON() (LATB3 = 0)
#define LED_3_OFF() (LATB3 = 1)

void uart_init(void);
void led_init(void);

#endif	/* GENERAL_H */

