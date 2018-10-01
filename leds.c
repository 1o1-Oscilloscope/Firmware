#include <xc.h>
#include <stdbool.h>
#include "leds.h"
#include "ports.h"

void LED_On(LED led){
    switch(led){
        case LED_1:
            LED_1_LAT = PIN_ON ;
            break;
        case LED_2:
            LED_2_LAT = PIN_ON ;
            break;
	case LED_3:
            LED_3_LAT = PIN_ON ;
            break;
        default:
            break;
    }
}

void LED_Off(LED led){
    switch(led){
        case LED_1:
            LED_1_LAT = PIN_OFF;
            break;
        case LED_2:
            LED_2_LAT = PIN_OFF;
            break;
	case LED_3:
            LED_3_LAT = PIN_OFF;
            break;
        default:
            break;
    }
}

void LED_Toggle(LED led){
    switch(led){
        case LED_1:
            LED_1_LAT ^= 1;
            break;
        case LED_2:
            LED_2_LAT ^= 1;
            break;
	case LED_3:
            LED_3_LAT ^= 1;
            break;
        default:
            break;
    }
}

bool LED_Get(LED led){
    switch(led){
        case LED_1:
            return ( ( LED_1_LAT == PIN_ON ) ? true : false );
        case LED_2:
            return ( ( LED_2_LAT == PIN_ON ) ? true : false );
	case LED_3:
            return ( ( LED_3_LAT == PIN_ON ) ? true : false );
        default:
            break;
    }
    return false;
}
