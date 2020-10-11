#include "gps_general.h"

#include <stdbool.h>
#include <xc.h>

void uart_init(void) {
    // Set Baud Rate Generator to generate baud rate of 9600
    // Bit 7 (BRGS) set to 1 to enable high speed BRG
    // Configure mode pins <3:0> 0000 sets the mode to 8 bit no parity
    U1CON0 = 0b10000000;

    // ((Fosc/9600) / 4) - 1 = 25 = 0x19
    U1BRGH = 0x0;
    U1BRGL = 0x19;

    //Set RX1 to PORT C7
    U1RXPPS = 0b010111;

    //Set the ON bit
    U1CON1 = 0x88;//1000 1000 Bit7=ON, Bit3 = RXBIMD(Receive Break Interrupt Mode Select bit)
    //Set U1TXIE to enable interrupt
    PIE3bits.U1RXIE = 1;
    //Enable reception by setting RXEN
    U1CON0bits.RXEN = 1;
    //Configure RX pin at C7
    LATC7 = 1;
    ANSELC7 = 0;

    U1ERRIRbits.U1FERIF = 0;
    //End of UART connection setup
}

void led_init(void) {
    TRISB1 = 0;
    LED_1_OFF();

    TRISB2 = 0;
    LED_2_OFF();
}

void led_1_heartbeat(void) {
    static bool led_on = false;
    if (led_on) {
        LED_1_OFF();
        led_on = false;
    } else {
        LED_1_ON();
        led_on = true;
    }
}
