/*
 * Graphical Oscilloscope Display
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   scope_display.h
 * 
 * @Summary
 *   Contains the glue logic to run the display for the oscilloscope.
*/

#ifndef SCOPE_DISPLAY_H
#define	SCOPE_DISPLAY_H


#include "common/screen.h"
#include "drivers/ssd1305.h"


#define M_EXPAND(...) __VA_ARGS__
#define FULLSIZE_LAYER(name)\
s_pixel_t M_EXPAND(name##_values)[XALG_COLUMNS][XALG_ROWS] = { 0 };\
screen_t M_EXPAND(name) = {\
	{XALG_COLUMNS, XALG_ROWS},\
	(s_pixel_t *) M_EXPAND(name##_values)\
}

#define LAYER_COUNT 4
#define TOAST_MAX_LENGTH 64
#define PIXELS_PER_DIV 16


#ifdef	__cplusplus
extern "C"
{
#endif


void sd_init       ();
void sd_task       ();
void sd_show_toast (char * text);
void sd_plot_data  (uint8_t * buffer, uint8_t size);


#ifdef	__cplusplus
}
#endif

#endif	/* SCOPE_DISPLAY_H */

