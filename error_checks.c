#include "canlib.h"

#include "mcc_generated_files/fvr.h"
#include "mcc_generated_files/adcc.h"

#include "timer.h"
#include "error_checks.h"

#include <stdlib.h>

void board_status_heartbeat(void) {
    uint32_t board_error_bitfield = 0;
    if (!check_bus_current_error()) {
        board_error_bitfield |= (1 << E_5V_OVER_CURRENT_OFFSET);
    }
    
    
}

//******************************************************************************
//                              STATUS CHECKS                                 //
//******************************************************************************

static bool check_bus_current_error(void){
    adc_result_t sense_raw_mV = ADCC_GetSingleConversion(channel_CURRENT) / 2;
    int curr_draw_mA = (sense_raw_mV) / 20;

    return curr_draw_mA <= OVERCURRENT_THRESHOLD_mA;
}