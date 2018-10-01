
#include "afe_gain.h"
#include "../ports.h"

void
afe_gain_set (afe_gain_t gain)
{
	switch(gain){
        case GAIN_1:
            A_0_LAT = PIN_ON;
			A_1_LAT = PIN_OFF;
			A_2_LAT = PIN_ON;
			A_EN_LAT = PIN_OFF;
            break;
        case GAIN_0_5:
            A_0_LAT = PIN_OFF;
			A_1_LAT = PIN_ON;
			A_2_LAT = PIN_ON;
			A_EN_LAT = PIN_OFF;
            break;
	case GAIN_0_1:
            A_0_LAT = PIN_OFF;
			A_1_LAT = PIN_OFF;
			A_2_LAT = PIN_OFF;
			A_EN_LAT = PIN_OFF;
            break;
	case GAIN_OFF:
    default:
			A_0_LAT = PIN_OFF;
			A_1_LAT = PIN_OFF;
			A_2_LAT = PIN_OFF;
			A_EN_LAT = PIN_ON;
            break;
    }
}