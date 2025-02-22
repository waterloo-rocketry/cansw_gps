#include "canlib/canlib.h"

#include "mcc_generated_files/adcc.h"
#include "mcc_generated_files/fvr.h"

#include "error_checks.h"
#include "timer.h"

#include <stdlib.h>

//******************************************************************************
//                              STATUS CHECKS                                 //
//******************************************************************************

bool check_5v_current_error(void) {
    adc_result_t sense_raw_mV = ADCC_GetSingleConversion(channel_CURRENT) / 2;
    int curr_draw_mA = (sense_raw_mV) / 20;

    can_msg_t msg;
    build_analog_data_msg(PRIO_LOW, millis(), SENSOR_5V_CURR, curr_draw_mA, &msg);
    txb_enqueue(&msg);

    if (curr_draw_mA > OVERCURRENT_THRESHOLD_mA) {
        return true;
    }

    return false;
}
