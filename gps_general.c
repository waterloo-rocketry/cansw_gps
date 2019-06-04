#include "gps_general.h"
#include <xc.h>

void uart_init(void) {
    //Set Baud Rate Generator to generate baud rate of 4800
    U1CON0 = 0; //Bit 7 = 0 (BRGS) //Configure mode pins <3:0> 0000 sets the mode to 8 bit no parity
    U1BRGH =  0x0; // 0000 0000 ((Fosc/4800) / 16) -1
    U1BRGL = 0xC; // 0000 1000

    //Set RX1 to PORT C7
    U1RXPPS = 0b10111;

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

    TRISB3 = 0;
    LED_3_OFF();
}