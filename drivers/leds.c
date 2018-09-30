/*
 * 1o1 LEDs Driver
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   leds.c
 * 
 * @Summary
 *   Interface to the debug LEDs on the 1o1 board.
*/

#include "leds.h"

#include <xc.h>
#include <stdbool.h>

#include "../ports.h"


#define LED_ON  1
#define LED_OFF 0


void
led_on (led_t led)
{
	switch (led)
	{
		case LED_1:
			LED_1_LAT = LED_ON;
			break;
		
		case LED_2:
			LED_2_LAT = LED_ON;
			break;
		
		case LED_3:
			LED_3_LAT = LED_ON;
			break;
		
		default:
			break;
	}
}

void
led_off (led_t led)
{
	switch (led)
	{
		case LED_1:
			LED_1_LAT = LED_OFF;
			break;
		
		case LED_2:
			LED_2_LAT = LED_OFF;
			break;
		
		case LED_3:
			LED_3_LAT = LED_OFF;
			break;
		
		default:
			break;
	}
}

void
led_toggle (led_t led)
{
	switch (led)
	{
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

bool
led_get (led_t led)
{
	bool result = false;

	switch (led)
	{
		case LED_1:
			result = ((LED_1_LAT == LED_ON) ? true : false);
			break;
		
		case LED_2:
			result = ((LED_2_LAT == LED_ON) ? true : false);
			break;
		
		case LED_3:
			result = ((LED_3_LAT == LED_ON) ? true : false);
			break;
		
		default:
			break;
	}
	
	return result;
}
