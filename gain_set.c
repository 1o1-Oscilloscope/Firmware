#include "gain_set.h"
#include "ports.h"

void Gain_Set(GAIN gain){
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
