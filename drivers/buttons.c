/*
 * 1o1 Buttons Driver
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   buttons.c
 * 
 * @Summary
 *   Interface to the buttons on the 1o1 board.
*/

#include "buttons.h"

#include <stdbool.h>

#include "../ports.h"

bool
button_read (button_t button)
{
	int state = 0;
	
	switch (button)
	{
		case BUTTON_1:
			state = BUT_1_PORT;
			break;
		
		case BUTTON_2:
			state = BUT_2_PORT;
			break;
		
		case BUTTON_3:
			state = BUT_3_PORT;
			break;
		
		case BUTTON_4:
			state = BUT_4_PORT;
			break;
		
		case BUTTON_5:
			state = BUT_5_PORT;
			break;
		
		case BUTTON_6:
			state = BUT_6_PORT;
			break;
		
		default:
			break;
    }
	
    if (state == PIN_ON)
	{
		return false;
	}
	else
	{
		return true;
	}
}
