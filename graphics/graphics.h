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
#include <stdbool.h>

#include "packed_graphics.h"

#ifdef	__cplusplus
extern "C"
{
#endif

void graphics_pack_layers (screen_t ** layers, uint8_t count,
						   packed_graphics_t * out, bool * enable);

bool graphics_fill_rect   (screen_t * screen, s_vector_t v0, s_vector_t v1,
						   s_pixel_t value);
void graphics_fill_screen (screen_t * screen, s_pixel_t value);
bool graphics_draw_line   (screen_t * screen, s_vector_t v0, s_vector_t v1,
						   s_pixel_t value);
bool graphics_fast_line   (screen_t * screen, s_vector_t v0, s_coord_t length,
						   bool vertical, s_pixel_t value);
bool graphics_dotted_line (screen_t * screen, s_vector_t v0, s_coord_t length,
					       bool vertical, s_coord_t spacing, s_pixel_t value);
bool graphics_draw_rect   (screen_t * screen, s_vector_t v0, s_vector_t v1,
						   s_pixel_t value);

bool graphics_copy_data     (screen_t * screen0, s_vector_t source,
							 s_vector_t size, screen_t * screen1,
							 s_vector_t dest);
bool graphics_overlay_data  (screen_t * screen0, s_vector_t source,
							 s_vector_t size, screen_t * screen1,
							 s_vector_t dest, bool subtract);


#ifdef	__cplusplus
}
#endif

#endif	/* GRAPHICS_H */
