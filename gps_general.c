#include <xc.h>

#include "gps_general.h"

void uart_init(void) {
	// Set Baud Rate Generator to generate baud rate of 9600
	// Bit 7 (BRGS) set to 1 to enable high speed BRG
	// Configure mode pins <3:0> 0000 sets the mode to 8 bit no parity
	U1CON0bits.BRGS = 1;
	U1CON0bits.MODE = 0;

	// _XTAL_FREQ / 9600 / 16 - 1
	U1BRGH = 0x4;
	U1BRGL = 0xE1;

	// Set RX1 to PORT C3
	U1RXPPS = 0b010011;

	// Set the ON bit
	//  Bit7=ON, Bit3 = RXBIMD(Receive Break Interrupt Mode Select bit)
	U1CON1 = 0b10001000;
	//  Run on overflow
	U1CON2bits.RUNOVF = 1;
	// Set U1TXIE to enable interrupt
	PIE3bits.U1RXIE = 1;
	// Enable reception by setting RXEN
	U1CON0bits.RXEN = 1;
	// Configure RX pin at C3
	LATC3 = 1;
	ANSELC3 = 0;
	TRISC3 = 1;

	U1ERRIRbits.U1FERIF = 0;
	// End of UART connection setup
}

void led_init(void) {
	TRISC0 = 0;
	LED_1_OFF();

	TRISC1 = 0;
	LED_2_OFF();
}

void led_1_heartbeat(void) {
	if (LATC0) {
		LED_1_OFF();
	} else {
		LED_1_ON();
	}
}
