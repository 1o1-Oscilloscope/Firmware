/*
 * Graphics Library
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   graphics.c
 * 
 * @Summary
 *   Provides drawing functions for use with screen_t.
*/

#include "graphics.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../common/screen.h"
#include "packed_graphics.h"


void
graphics_pack_layers (screen_t ** layers, uint8_t count,
					  packed_graphics_t * out, bool * enable)
{
	bool based = false;
	for (uint8_t i = 0; i < count; i++)
	{
		if ((NULL == enable) || (enable[i]))
		{
			screen_t * layer = layers[i];
			for (s_coord_t x = 0; x < SMIN(layer->width, out->columns); x++)
			{
				if (!based)
				{
					for (s_coord_t y = 0; y < out->pages; y++)
					{
						PGPIXEL(out, x, y) = 0;
					}	
				}
				
				for (s_coord_t y = 0; y < SMIN(layer->height, out->pages * 8);
						y++)
				{
					PGPIXEL(out, x, y / 8) |= 
							((SPIXEL(layer, x, y) ? 1 : 0) << (y % 8));
				}
			}
			based = true;
		}
	}
}

void
graphics_apply_mask (screen_t * image, screen_t * mask)
{
	for (s_coord_t x = 0; x < SMIN(image->width, mask->width); x++)
	{
		for (s_coord_t y = 0; y < SMIN(image->height, mask->width); y++)
		{
			if (!SPIXEL(mask, x, y))
			{
				SPIXEL(image, x, y) = 0;
			}
		}
	}
}


bool
graphics_fill_rect (screen_t * screen, s_coord_t x0, s_coord_t y0, s_coord_t x1,
					s_coord_t y1, s_pixel_t value)
{
	if (!(SPIXEL_CHECK(screen, x0, y0) && SPIXEL_CHECK(screen, x1, y1)))
	{
		return false;
	}
	
	for (s_coord_t x = x0; x <= x1; x++)
	{
		for (s_coord_t y = y0; y <= y1; y++)
		{
			SPIXEL(screen, x, y) = value;
		}
	}
	
	return true;
}

bool
graphics_draw_line (screen_t * screen, s_coord_t x0, s_coord_t y0, s_coord_t x1,
					s_coord_t y1, s_pixel_t value)
{
	if (!(SPIXEL_CHECK(screen, x0, y0) && SPIXEL_CHECK(screen, x1, y1)))
	{
		return false;
	}
	
	int dx = x1 - x0;
	int dy = y1 - y0;
	unsigned int pmax = (unsigned int)SMAX(abs(dx), abs(dy));
	float a = (float)(dx) / (float)(pmax);
	float b = (float)(dy) / (float)(pmax);
	
	for (unsigned int p = 0; p < pmax; p++)
	{
		s_coord_t x = SMAX(SMIN(x0 + floorf(p * a), screen->width - 1), 0);
		s_coord_t y = SMAX(SMIN(y0 + floorf(p * b), screen->height - 1), 0);
		SPIXEL(screen, x, y) = value;
	}
	
	return true;
}


bool
graphics_overlay_data (screen_t * screen0, s_coord_t x0, s_coord_t y0,
					s_coord_t width, s_coord_t height, screen_t * screen1,
					s_coord_t x1, s_coord_t y1)
{
	if (!(SPIXEL_CHECK(screen0, x0, y0) && SPIXEL_CHECK(screen1, x1, y1)))
	{
		return false;
	}
	
	if (x0 + width > screen0->width)
	{
		width = screen0->width - x0;
	}
	if (x1 + width > screen1->width)
	{
		width = screen1->width - x1;
	}
	if (y0 + height > screen0->height)
	{
		height = screen0->height - y0;
	}
	if (y1 + height > screen1->height)
	{
		height = screen1->height - y1;
	}
	
	for (s_coord_t xi = 0; xi < width; xi++)
	{
		for (s_coord_t yi = 0; yi < height; yi++)
		{
			SPIXEL(screen1, x1 + xi, y1 + yi) |=
					SPIXEL(screen0, x0 + xi, y0 + yi);
		}
	}
	
	return true;
}
