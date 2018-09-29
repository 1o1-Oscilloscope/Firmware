/*
 * Graphics Library
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   graphics.h
 * 
 * @Summary
 *   Provides drawing functions for use with screen_t.
*/

#ifndef GRAPHICS_H
#define	GRAPHICS_H

#include "../common/screen.h"

#include <stdint.h>

#include "packed_graphics.h"

#ifdef	__cplusplus
extern "C"
{
#endif

void graphics_pack_layers (screen_t ** layers, uint8_t count,
						   packed_graphics_t * out, bool * enable);
void graphics_apply_mask (screen_t * image, screen_t * mask);

bool graphics_fill_rect (screen_t * screen, s_coord_t x0, s_coord_t y0,
						 s_coord_t x1, s_coord_t y1, s_pixel_t value);
bool graphics_draw_line (screen_t * screen, s_coord_t x0, s_coord_t y0,
						 s_coord_t x1, s_coord_t y1, s_pixel_t value);

bool graphics_overlay_data (screen_t * screen0, s_coord_t x0, s_coord_t y0,
							s_coord_t width, s_coord_t height,
							screen_t * screen1, s_coord_t x1, s_coord_t y1);


#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */
