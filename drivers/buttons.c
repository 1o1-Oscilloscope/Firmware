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


static const button_t buttons[BUTTON_COUNT] = {
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6
};
static bool button_state[BUTTON_COUNT] = { 0 };
static bool button_press[BUTTON_COUNT] = { 0 };


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


void
button_task ()
{
	for (uint8_t button = 0; button < BUTTON_COUNT; button++)
	{
		if ((!button_state[button]) && button_read((button_t)button))
		{
			button_state[button] = true;
			button_press[button] = true;
		}
		else if (button_state[button] && (!button_read((button_t)button)))
		{
			button_state[button] = false;
		}
	}
}

bool
button_pressed (button_t button)
{
	if (button_press[(uint8_t) button])
	{
		button_press[(uint8_t) button] = false;
		return true;
	}
	else
	{
		return false;
	}
}
