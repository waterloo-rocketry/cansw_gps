#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/message_types.h"
#include "canlib/util/timing_util.h"
#include "canlib/util/can_tx_buffer.h"

#include "mcc_generated_files/fvr.h"
#include "mcc_generated_files/adcc.h"

#include "config.h"
#include "timer.h"
#include "gps_module.h"
#include "gps_general.h"
#include "error_checks.h"

#include <xc.h>
#include <stdlib.h>

// Memory pool for CAN transmit buffer
uint8_t tx_pool[500];
static void can_msg_handler(const can_msg_t *msg);

static void send_status_ok(void);
static void send_status_error_module(void);

static volatile bool recieved_first_message = false;
static volatile bool seen_can_message = false;

int main(void) {

    // Set frequency to be 48 MHZ
    OSCFRQbits.FRQ = 0b0111;

    ADCC_Initialize();
    FVR_Initialize();

    // Enable global interrupts
    INTCON0bits.GIE = 1;

    uart_init();
    led_init();
    gps_init();
    timer0_init();

    // Set up CAN TX
    TRISC0 = 0;
    RC0PPS = 0x33;

    // Set up CAN RX
    TRISC1 = 1;
    ANSELC1 = 0;
    CANRXPPS = 0x11;

    // set up CAN module
    can_timing_t can_setup = {
        .brp      =  7,
        .sjw      =  3,
        .btlmode  =  1,
        .sam      =  0,
        .seg1ph   =  4,
        .prseg    =  0,
        .seg2ph   =  4
    };
    can_init(&can_setup, can_msg_handler);
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    uint32_t last_millis = millis();
    uint32_t last_message_millis = millis();

    // Turn LED 1 on
    LED_1_ON();

    // Wait for the first message
    while (!recieved_first_message) {
        CLRWDT(); // feed the watchdog, which is set for 256ms
        
        if (seen_can_message) {
            seen_can_message = false;
            last_message_millis = millis();
        }
        
        if (millis() - last_message_millis > MAX_BUS_DEAD_TIME_ms) {
            // We've got too long without seeing a valid CAN message (including one of ours)
            RESET();
        }
        
        if (millis() - last_millis > 5000) {
            // Haven't received anything, try resetting the gps
            LATC2 = 0;
            __delay_ms(100);
            LATC2 = 1;
            __delay_ms(100);

            send_status_error_module();
            last_millis = millis();
        }
    }

    while(1) {
        CLRWDT(); // feed the watchdog, which is set for 256ms
        
        if (seen_can_message) {
            seen_can_message = false;
            last_message_millis = millis();
        }
        
        if (millis() - last_message_millis > MAX_BUS_DEAD_TIME_ms) {
            // We've got too long without seeing a valid CAN message (including one of ours)
            RESET();
        }
        
        if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {
            bool status_ok = check_bus_current_error();
            if (status_ok) {
                send_status_ok();
            }

            led_1_heartbeat();
            last_millis = millis();
        }
        txb_heartbeat();
    }

    return (EXIT_SUCCESS);
}

static void __interrupt() interrupt_handler() {
    if (PIR5) {
        // Handle CAN
        can_handle_interrupt();
    }

    // UART message
    if (PIR3bits.U1RXIF == 1) {
        recieved_first_message = true;

        if (U1ERRIRbits.FERIF) {
            // UART frame error
        }

        if (U1ERRIRbits.RXFOIF) {
            // UART overflowed
            U1ERRIRbits.RXFOIF = 0;
        }

        gps_handle_byte(U1RXB);

        PIR3bits.U1RXIF = 0;
    }

    // Timer0 has overflowed - update millis() function
    // This happens approximately every 500us
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

// This is called from within can_handle_interrupt()
static void can_msg_handler(const can_msg_t *msg) {
    seen_can_message = true;
    
    uint16_t msg_type = get_message_type(msg);
    int dest_id = -1;

    switch (msg_type) {
        case MSG_LEDS_ON:
            LED_1_ON();
            LED_2_ON();
            break;

        case MSG_LEDS_OFF:
            LED_1_OFF();
            LED_2_OFF();
            break;

        case MSG_RESET_CMD:
            dest_id = get_reset_board_id(msg);
            if (dest_id == BOARD_UNIQUE_ID || dest_id == 0 ){
                RESET();
            }
            break;
        default:
            // all the other ones - do nothing
            break;
    }
}

// Send a CAN message with nominal status
static void send_status_ok(void) {
    can_msg_t board_stat_msg;
        build_board_stat_msg(millis(), E_NOMINAL, NULL, 0, &board_stat_msg);       
    // send it off at low priority
    txb_enqueue(&board_stat_msg);
}

static void send_status_error_module(void) {
    can_msg_t board_stat_msg;
        build_board_stat_msg(millis(), E_GPS, NULL, 0, &board_stat_msg);       
    // send it off at low priority
    txb_enqueue(&board_stat_msg);
}
