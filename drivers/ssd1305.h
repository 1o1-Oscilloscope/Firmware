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
#define SSD1305_H

#include <xc.h>

#include "../common/screen.h"
#include "../graphics/packed_graphics.h"

#define XALG_START_COLUMN 18
#define XALG_COLUMNS 96
#define XALG_END_COLUMN (XALG_START_COLUMN + XALG_COLUMNS - 1)
#define XALG_ROWS 64
#define XALG_START_PAGE 0
#define XALG_PAGES (XALG_ROWS / 8)
#define XALG_END_PAGE (XALG_START_PAGE + XALG_PAGES - 1)

#ifdef	__cplusplus
extern "C"
{
#endif


void ssd1305_init    ();
void ssd1305_disable ();

void ssd1305_clear ();
void ssd1305_write_all (packed_graphics_t * graphics);
void ssd1305_write_all_screen (screen_t * screen);


#ifdef	__cplusplus
}
#endif

#endif	/* SSD1305_H */

