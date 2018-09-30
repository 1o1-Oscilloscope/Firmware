/*
 * 1o1 Port Definitions
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   ports.c
 * 
 * @Summary
 *   Configures the IO ports used by the hardware.
*/

#include "ports.h"

#include <xc.h>


void
ports_init ()
{
	LED_1_LAT = 0;
	LED_1_PORT = 0;
	LED_1_TRIS = PORT_OUTPUT;
	LED_1_ANSEL = 0;

	LED_2_LAT = 0;
	LED_2_PORT = 0;
	LED_2_TRIS = PORT_OUTPUT;
	LED_2_ANSEL = 0;

	LED_3_LAT = 0;
	LED_3_PORT = 0;
	LED_3_TRIS = PORT_OUTPUT;
	LED_3_ANSEL = 0;

	OLED_RES_LAT = 0;
	OLED_RES_PORT = 0;
	OLED_RES_TRIS = PORT_OUTPUT;

	BUT_1_LAT = 0;
	BUT_1_PORT = 0;
	BUT_1_TRIS = PORT_INPUT;
	BUT_1_CNPU = 1;
	BUT_1_ANSEL = 0;

	BUT_2_LAT = 0;
	BUT_2_PORT = 0;
	BUT_2_TRIS = PORT_INPUT;
	BUT_2_CNPU = 1;
	BUT_2_ANSEL = 0;

	BUT_3_LAT = 0;
	BUT_3_PORT = 0;
	BUT_3_TRIS = PORT_INPUT;
	BUT_3_CNPU = 1;
	BUT_3_ANSEL = 0;

	BUT_4_LAT = 0;
	BUT_4_PORT = 0;
	BUT_4_TRIS = PORT_INPUT;
	BUT_4_CNPU = 1;
	BUT_4_ANSEL = 0;

	BUT_5_LAT = 0;
	BUT_5_PORT = 0;
	BUT_5_TRIS = PORT_INPUT;
	BUT_5_CNPU = 1;
	BUT_5_ANSEL = 0;

	BUT_6_LAT = 0;
	BUT_6_PORT = 0;
	BUT_6_TRIS = PORT_INPUT;
	BUT_6_CNPU = 1;
	BUT_6_ANSEL = 0;
}
