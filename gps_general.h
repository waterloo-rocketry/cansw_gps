#ifndef GENERAL_H
#define GENERAL_H

#define _XTAL_FREQ 48000000
#define MAX_LOOP_TIME_DIFF_ms 500
#define MAX_BUS_DEAD_TIME_ms 1000

#define LED_1_ON() (LATB1 = 1)
#define LED_1_OFF() (LATB1 = 0)
#define LED_2_ON() (LATB2 = 1)
#define LED_2_OFF() (LATB2 = 0)

void uart_init(void);

void led_init(void);
void led_1_heartbeat(void);

#endif /* GENERAL_H */
