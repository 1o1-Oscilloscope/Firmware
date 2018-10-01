#include "button.h"
#include "ports.h"

bool Button_Get(BUTTON button){
	switch (button){
		case BUTTON_1:
			return ( ( BUT_1_PORT == PIN_ON ) ? true : false );
		case BUTTON_2:
			return ( ( BUT_2_PORT == PIN_ON ) ? true : false );
		case BUTTON_3:
			return ( ( BUT_3_PORT == PIN_ON ) ? true : false );
		case BUTTON_4:
			return ( ( BUT_4_PORT == PIN_ON ) ? true : false );
		case BUTTON_5:
			return ( ( BUT_5_PORT == PIN_ON ) ? true : false );
		case BUTTON_6:
			return ( ( BUT_6_PORT == PIN_ON ) ? true : false );
		default:
            break;
    }
    return false;
}
