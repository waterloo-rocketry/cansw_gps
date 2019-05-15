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

#include <xc.h>

static void can_msg_handler(can_msg_t *msg);
static void send_status_ok(void);

// Memory pool for CAN transmit buffer
uint8_t tx_pool[100];



int main(void) {
    /*
    //set up UART connection
    
    //Set RX1 to PORT C7
    U1RXPPS = 0b1 0111;
    //set port C3 as TX1
    RC3PPS = 0b01 0011;
    */
    
    //Set port  B1 as output pin
    TRISB1 = 0;
    // Write a 1 to port B1. This should write to B1
    PORTB |= 0x2;
    
    
    return (EXIT_SUCCESS);
}
