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
#include <string.h>

#include <xc.h>
#include <stdlib.h>
#define _XTAL_FREQ 1000000

// Memory pool for CAN transmit buffer
uint8_t tx_pool[500];
char GPGGA[5] = {'G', 'P', 'G', 'G', 'A'};//"GPGGA"
char msgType[5];
int msgTypeIndex;
char timeStamp[9];
int timeStampIndex;
char latitude[10];
int latitudeIndex;
char latdir;
char longitude[10];
int longitudeIndex;
char longdir;
char qualind;
char numOfSat[3];
int numOfSatIndex;
char HDOP[3];
int HDOPIndex;
char ANTALT[10];
int ANTALTIndex;
char ALTUNIT[2];
int ALTUNITIndex;

int x = 0;

char buffer[100];
int y = 0;
char buffer1[100];
int y1 = 0;
char buffer2[100];
int y2 = 0;
char buffer3[100];
int y3 = 0;


uint16_t state = 0;
/* STATES:
 0 IDLE
 1 START
 2 MESSAGETYPE
 3 TIMESTAMP
 4 LATITUDE
 5 LATITUDE DIRECTION (N-S)
 6 LONGITUDE 
 7 LONGITUDE DIRECTION (E-W)
 8 Quality Indicator: 1 = Uncorrected coordinate 2 = Differentially correct coordinate (e.g., WAAS, DGPS) 4 = RTK Fix coordinate (centimeter precision) 5 = RTK Float (decimeter precision.
 9 NUMBER OF SATELLITES 
 10 HDOP (horizontal dilution of precision)
 11 ALTITUDE OF ANTENNA
 12 ALTITUDE UNITS
 13 STOP
 14 ERROR
 */


int main(void) {
    
    // Enable global interrupts
    INTCON0bits.GIE = 1;
    
    //set up UART connection
    
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

    
    //timer setup
    timer0_init();
    
    //GPS PINOUT setup
    
    //Set port  B1 as output pin (LED 3)
    TRISB1 = 0;
    TRISB2 = 0;
    TRISB3 = 0;
    LATB1 = 0;
    LATB2 = 0;
    LATB3 = 0;
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
    __delay_ms(250);
    LATC2 = 0;
    // Write a 1 to port C6 (RESET) Writing a 1 because active low
    LATC6 = 1;
    
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
    }
    if (PIR3bits.U1RXIF) {
        //Handle GPS Interrupt
        if (U1ERRIR) {
            //error
            
            U1ERRIR = 0; //ignore all errors
        } 
        if (U1RXB) {
            
            //character received
            switch(U1RXB) {
                case '$':
                    state = 2;
                    msgTypeIndex = 0;
                    timeStampIndex = 0;
                    latitudeIndex = 0;
                    longitudeIndex = 0;
                    numOfSatIndex = 0;
                    HDOPIndex = 0;
                    ANTALTIndex = 0;
                    ALTUNITIndex = 0;
                    break;
                   
                case ',':
                    if (state < 13) {
                        if (state == 2) {
                             if ((msgType[0] == GPGGA[0]) && (msgType[1] == GPGGA[1]) && (msgType[2] == GPGGA[2]) && (msgType[3] == GPGGA[3]) && (msgType[4] == GPGGA[4])) {
                                //if we read a GPGGA signal, then the state machine carries on
                                state++;
                                LATB1 ^= 1;
                                LATB2 ^= 1;
                                LATB3 ^= 1;
                                break;
                            } else {
                                 //if we dont read a GPGGA signal, then we wont care about the message for now
                                state = 0;

                            }
                        }
                        
                    }
                    break;
                default:

                switch(state) {
                    case 0://idle do nothing
                        break;
                    case 1://start, for debugging purposes
                        break;
                    case 2:
                        msgType[msgTypeIndex++] = U1RXB;
                        
                        break;
                    case 3:
                        //LATB1 ^= 1;
                        //LATB2 ^= 1;
                        //LATB3 ^= 1;
                        
                        timeStamp[timeStampIndex++] = U1RXB;
                        break;
                    case 4:
                        latitude[latitudeIndex++] = U1RXB;
                        break;
                    case 5:
                        latdir = U1RXB;
                        break;
                    case 6:
                        longitude[longitudeIndex++] = U1RXB;
                        break;
                    case 7:
                        longdir = U1RXB;
                        break;
                    case 8:
                        qualind = U1RXB;
                        break;
                    case 9:
                        numOfSat[numOfSatIndex++] = U1RXB;
                        break;
                    case 10:
                        HDOP[HDOPIndex++] = U1RXB;
                        break;
                    case 11:
                        ANTALT[ANTALTIndex++] = U1RXB;
                        break;
                    case 12:
                        ALTUNIT[ALTUNITIndex++] = U1RXB;
                        if (ALTUNITIndex == 3) {
                            state++;
                        }
                        break;
                    case 13://STOP, wait for next
                        break;
                    case 14: //ERROR state
                        break;
                    default: // Should be unreachable
                        break;
                }
            }
            
        }
        //Clear Interrupt bit
        PIR3bits.U1RXIF = 0;
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}