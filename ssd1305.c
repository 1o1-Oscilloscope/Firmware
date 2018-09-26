/*
 * Solomon Systech SSD1305 Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   ssd1305.c
 * 
 * @Summary
 *   Interface to control SSD1305 based OLED display. Written for Electronic
 *   Assembly GmbH EA W096064-XALG display on 1o1 v1.0 board.
*/

#include "ssd1305.h"
#include "ports.h"

void
ssd1305_init()
{
	OLED_RES_LAT = LOW;
	OLED_RES_PORT = 0;
	OLED_RES_TRIS = PORT_OUTPUT;
}


void
ssd1305_enable()
{
	OLED_RES_LAT = LOW;
}

void
ssd1305_disable()
{
	OLED_RES_LAT = HIGH;
}
