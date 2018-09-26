/*
 * Solomon Systech SSD1305 Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   ssd1305.h
 * 
 * @Summary
 *   Interface to control SSD1305 based OLED display. Written for Electronic
 *   Assembly GmbH EA W096064-XALG display on 1o1 v1.0 board.
*/

#ifndef SSD1305_H
#define	SSD1305_H

#include <xc.h>

#ifdef	__cplusplus
extern "C"
{
#endif


void ssd1305_init();

void ssd1305_enable();
void ssd1305_disable();


#ifdef	__cplusplus
}
#endif

#endif	/* SSD1305_H */

