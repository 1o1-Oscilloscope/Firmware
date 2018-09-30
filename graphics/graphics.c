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
			for (s_coord_t x = 0; x < SMIN(layer->size.x, out->columns); x++)
			{
				if (!based)
				{
					for (s_coord_t y = 0; y < out->pages; y++)
					{
						PGPIXEL(out, x, y) = 0;
					}	
				}
				
				for (s_coord_t y = 0; y < SMIN(layer->size.y, out->pages * 8);
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
	for (s_coord_t x = 0; x < SMIN(image->size.x, mask->size.y); x++)
	{
		for (s_coord_t y = 0; y < SMIN(image->size.y, mask->size.y); y++)
		{
			if (!SPIXEL(mask, x, y))
			{
				SPIXEL(image, x, y) = 0;
			}
		}
	}
}


bool
graphics_fill_rect (screen_t * screen, s_vector_t v0, s_vector_t v1,
					s_pixel_t value)
{
	if (!(S_VECTOR_CHECK(screen, v0) && S_VECTOR_CHECK(screen, v1)))
	{
		return false;
	}
	
	for (s_coord_t x = v0.x; x <= v1.x; x++)
	{
		for (s_coord_t y = v0.y; y <= v1.y; y++)
		{
			SPIXEL(screen, x, y) = value;
		}
	}
	
	return true;
}

bool
graphics_draw_line (screen_t * screen, s_vector_t v0, s_vector_t v1,
					s_pixel_t value)
{
	if (!(S_VECTOR_CHECK(screen, v0) && S_VECTOR_CHECK(screen, v1)))
	{
		return false;
	}
	
	s_vector_t diff = S_VECTOR_SUB(v1, v0);
	unsigned int pmax = (unsigned int)SMAX(abs(diff.x), abs(diff.y));
	float a = (float)(diff.x) / (float)(pmax);
	float b = (float)(diff.y) / (float)(pmax);
	
	for (unsigned int p = 0; p < pmax; p++)
	{
		s_coord_t x = SMAX(SMIN(v0.x + floorf(p * a), screen->size.x - 1), 0);
		s_coord_t y = SMAX(SMIN(v0.y + floorf(p * b), screen->size.y - 1), 0);
		SPIXEL(screen, x, y) = value;
	}
	
	return true;
}

bool
graphics_fast_line (screen_t * screen, s_vector_t v0, s_coord_t length,
					bool vertical, s_pixel_t value)
{
	if (length < 0)
	{
		if (vertical)
		{
			v0.y += (length + 1);
		}
		else
		{
			v0.x += (length + 1);
		}
		length = -length;
	}
	
	if (!(S_VECTOR_CHECK(screen, v0) &&
		(vertical || S_COORD_CHECK(screen, v0.x + length - 1, v0.y)) &&
		(!vertical || S_COORD_CHECK(screen, v0.x, v0.y + length - 1))))
	{
		return false;
	}
	
	for (s_coord_t i = 0; i < length; i++)
	{
		if (vertical)
		{
			SPIXEL_V(screen, S_VECTOR_ADD(v0, S_VECTOR(0, i))) = value;
		}
		else
		{
			SPIXEL_V(screen, S_VECTOR_ADD(v0, S_VECTOR(i, 0))) = value;
		}
	}
	
	return true;
}

bool
graphics_draw_rect (screen_t * screen, s_vector_t v0, s_vector_t v1,
					s_pixel_t value)
{
	if (!(S_VECTOR_CHECK(screen, v0) && S_VECTOR_CHECK(screen, v1)))
	{
		return false;
	}
	
	s_vector_t diff = S_VECTOR_ADD(S_VECTOR_SUB(v1, v0), S_VECTOR_ONE);
	graphics_fast_line(screen, v0, diff.y, true, value);
	graphics_fast_line(screen, v0, diff.x, false, value);
	graphics_fast_line(screen, v1, -(diff.y), true, value);
	graphics_fast_line(screen, v1, -(diff.x), false, value);
	
	return true;
}


bool
graphics_copy_data (screen_t * screen0, s_vector_t source, s_vector_t size,
					screen_t * screen1, s_vector_t dest)
{
	if (!(S_VECTOR_CHECK(screen0, source) && S_VECTOR_CHECK(screen1, dest)))
	{
		return false;
	}
	s_vector_t check_size = S_VECTOR_SUB(size, S_VECTOR_ONE);
	if (!(S_VECTOR_CHECK(screen0, S_VECTOR_ADD(source, check_size)) &&
		S_VECTOR_CHECK(screen1, S_VECTOR_ADD(dest, check_size))))
	{
		return false;
	}
	
	
	for (s_coord_t xi = 0; xi < size.x; xi++)
	{
		for (s_coord_t yi = 0; yi < size.y; yi++)
		{
			s_vector_t offset = S_VECTOR(xi, yi);
			SPIXEL_V(screen1, S_VECTOR_ADD(dest, offset)) =
					SPIXEL_V(screen0, S_VECTOR_ADD(source, offset));
		}
	}
	
	return true;
}

bool
graphics_overlay_data (screen_t * screen0, s_vector_t source, s_vector_t size,
					   screen_t * screen1, s_vector_t dest, bool subtract)
{
	if (!(S_VECTOR_CHECK(screen0, source) && S_VECTOR_CHECK(screen1, dest)))
	{
		return false;
	}
	
	if (source.x + size.x > screen0->size.x)
	{
		size.x = screen0->size.x - source.x;
	}
	if (dest.x + size.x > screen1->size.x)
	{
		size.x = screen1->size.x - dest.x;
	}
	if (source.y + size.y > screen0->size.y)
	{
		size.y = screen0->size.y - source.y;
	}
	if (dest.y + size.y > screen1->size.y)
	{
		size.y = screen1->size.y - dest.y;
	}
	
	for (s_coord_t xi = 0; xi < size.x; xi++)
	{
		for (s_coord_t yi = 0; yi < size.y; yi++)
		{
			s_vector_t offset = S_VECTOR(xi, yi);
			if (subtract)
			{
				SPIXEL_V(screen1, S_VECTOR_ADD(dest, offset)) &=~
						SPIXEL_V(screen0, S_VECTOR_ADD(source, offset));
			}
			else
			{
				SPIXEL_V(screen1, S_VECTOR_ADD(dest, offset)) |=
						SPIXEL_V(screen0, S_VECTOR_ADD(source, offset));
			}
		}
	}
	
	return true;
}
