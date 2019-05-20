/*
 * File:   main.c
 * Author: Aidan.Ha@ibm.com
 *
 * Created on May 13, 2019, 10:29 PM
 */

#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "config.h"
#include "timer.h"
#include <stdio.h>

#include <xc.h>

#define _XTAL_FREQ 1000000

static void can_msg_handler(can_msg_t *msg);
static void send_status_ok(void);

// Memory pool for CAN transmit buffer
uint8_t tx_pool[100];



int main(void) {
    
    // Enable global interrupts
    INTCON0bits.GIE = 1;
    
    //set up UART connection
    
    //Set Baud Rate Generator to generate baud rate of 4800
    U1CON0 = 0; //Bit 7 = 0 (BRGS)
    U1BRGH = 18; // 0001 0010
    U1BRGL = 192; // 1100 0000
    //Set RX1 to PORT C7
    U1RXPPS = 0b1 0111;
    //Configure mode pins <3:0> 0000 sets the mode to 8 bit no parity
    U1CON0 |= 0; 
    //Set the ON bit
    U1CON1 = 136;//1000 1000 Bit7=ON, Bit3 = RXBIMD(Receive Break Interrupt Mode Select bit)
    //Set U1TXIE to enable interrupt
    PIE3.U1RXIE = 1;
    //Enable reception by setting RXEN
    U1CON0 |= 16; //Bit4=RXEN,
    
    //End of UART connection setup

    
    //timer setup
    timer0_init();
    
    //GPS PINOUT setup
    
    //Set port  B1 as output pin (LED 3)
    TRISB3 = 0;
    //SET port C4 as output pin (WAKEUP) (This might not be needed during power_up, but i'll leave this here for reference later)
    TRISC4 = 0;
    //Set port C6 as output pin (RESET)
    TRISC6 = 0;
    //Set port C2 as output pin (ON_OFF)
    TRISC2 = 0;
    
    // Write a 1 to port C4 (WAKEUP)
    LATC4 = 1;
    //Toggle C2 for first startup after power on
    LATC2 = 1;
    __delay_ms(300);
    LATC2 = 0;
    // Write a 0 to port C6 (RESET) Writing a 1 because active low
    LATC6 = 1;
    // Write a 1 to port B1 (LED 3)
    LATB3 = 1;
    
    //end of GPS PINOUT setup
    
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
    } else if (PIR3.U1RXIF) {
        //Handle GPS Interrupt
        if (U1ERRIR) {
            //error
            LATB3 = 1;
        } else if (U1RXB) {
            //data received. 
            LATB1 = 1;
        }
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}