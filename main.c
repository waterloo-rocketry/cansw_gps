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

static volatile uint8_t recieved_first_message = 0;

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
        .brp      = 47,
        .sjw      =  3,
        .btlmode  =  1,
        .sam      =  0,
        .seg1ph   =  4,
        .prseg    =  0,
        .seg2ph   =  4
    };
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    uint32_t last_millis = millis();

    // Turn LED 1 on
    LED_1_LAT = 1;

    // Wait for the first message
    while (!recieved_first_message) {
        if (millis() - last_millis > 5000) {
            // Haven't received anything, try reset
            LATC2 = 0;
            __delay_ms(100);
            LATC2 = 1;
            __delay_ms(100);

            send_status_error_module();
            last_millis = millis();
        }
    }

    while(1) {
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
        recieved_first_message = 1;

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
    if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
        timer0_handle_interrupt();
        PIR3bits.TMR0IF = 0;
    }
}

// This is called from within can_handle_interrupt()
static void can_msg_handler(const can_msg_t *msg) {
    uint16_t msg_type = get_message_type(msg);
    switch (msg_type) {
        case MSG_LEDS_ON:
            LED_1_LAT = 1;
            LED_2_LAT = 1;
            break;

        case MSG_LEDS_OFF:
            LED_1_LAT = 0;
            LED_2_LAT = 0;
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
