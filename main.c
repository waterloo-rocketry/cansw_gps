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


int main(void) {
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
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    uint32_t last_millis = millis();

    __delay_ms(300);

    while (!RecievedFirstMessage) {
        //If we haven't received anything, toggle ON_OFF.
        LATC2 = 1;
        __delay_ms(300);
        LATC2 = 0;
        __delay_ms(300);
    }
    LATB3 = 0;

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
        if (RecievedFirstMessage == 0) {
            //we received something from uart for the first time.
            RecievedFirstMessage = 1;
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

// This is called from within can_handle_interrupt()
static void can_msg_handler(const can_msg_t *msg) {
    uint16_t msg_type = get_message_type(msg);
    switch (msg_type) {
        case MSG_GENERAL_CMD:
            // nothing right now
            break;

        case MSG_LEDS_ON:
            LED_1_ON();
            LED_2_ON();
            LED_3_ON();
            break;

        case MSG_LEDS_OFF:
            LED_1_OFF();
            LED_2_OFF();
            LED_3_OFF();
            break;

        // all the other ones - do nothing
        default:
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