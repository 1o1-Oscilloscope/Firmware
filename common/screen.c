/*
 * Common Screen Interface (Greyscale)
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   screen.c
 * 
 * @Summary
 *   Provides a standard screen/framebuffer interface.
 *   This revision implements a monochrome color model.
*/

#include "screen.h"

#include <math.h>
#include <stdbool.h>


s_pixel_t
s_compositef (s_pixel_t bottom, s_pixel_t top, float alpha)
{
	if (alpha > 0.5f)
	{
		return top;
	}
	else
	{
		return bottom;
	}
}

bool
s_validate_coords (screen_t * screen, s_coord_t x, s_coord_t y)
{
	return (x >= 0 && x < screen->width && y >= 0 && y < screen->height);
}
