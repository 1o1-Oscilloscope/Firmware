/*
 * 1o1 LEDs Driver
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   AC-Out.c
 * 
 * @Summary
 *   Interface to the AC switch has on the Open ATS Board
 */

#include "AC-Out.h"

#include <xc.h>
#include <stdbool.h>

#include "../ports.h"


#define AC_ON  1
#define AC_OFF 0

void AC_on(ac_t ac) {
    switch (ac) {
        case AC_1:
            EN_2_LAT = AC_OFF;
            EN_1_LAT = AC_ON;
            break;

        case AC_2:
            EN_1_LAT = AC_OFF;
            EN_2_LAT = AC_ON;
            break;

        default:
            break;
    }
}

void AC_off(void) {
    EN_1_LAT = AC_OFF;
    EN_2_LAT = AC_OFF;
}
