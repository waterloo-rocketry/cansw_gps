#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "config.h"
#include "timer.h"
#include <string.h>
#include "gps_module.h"
#include "gps_general.h"

#include <xc.h>
#include <stdlib.h>

// Memory pool for CAN transmit buffer
uint8_t tx_pool[500];

int main(void) {
    // Enable global interrupts
    INTCON0bits.GIE = 1;

    uart_init();
    led_init();
    gps_init();
    timer0_init();

    //Set port  B1 as output pin (LED 3)
    TRISB1 = 0;
    TRISB2 = 0;
    TRISB3 = 0;
    LATB1 = 0;
    LATB2 = 0;
    LATB3 = 0;

    uint32_t last_millis = millis();

    //Main Loop
    while(1)
    {
        /*if (millis() - last_millis > 1000) {
            LATB3 ^= 1;
            last_millis = millis();
        }
         */
        //__delay_ms(1000);

    }
    return (EXIT_SUCCESS);
}

static void __interrupt() interrupt_handler() {
    if (PIR5) {
        //Handle CAN
        can_handle_interrupt();
    }
    
    // deal with incoming UART bytes
    if (PIR3bits.U1RXIF) {
        //Handle GPS Interrupt
        if (U1ERRIR) {
            //error
            U1ERRIR = 0; //ignore all errors
        }
        uint8_t byte = U1RXB;
        gps_handle_byte(byte);
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}