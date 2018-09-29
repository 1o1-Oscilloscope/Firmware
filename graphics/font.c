/*
 * Raster Font Module
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   font.c
 * 
 * @Summary
 *   Provides font and glyph interfaces and drawing functions.
*/

#include "font.h"

#include <stdint.h>
#include <stdlib.h>

#include "../common/screen.h"
#include "graphics.h"


font_error_t
font_write (font_t * font, char * text, int length, screen_t * screen,
			s_coord_t x0, s_coord_t y0, s_coord_t wrap_width)
{
	if (!SPIXEL_CHECK(screen, x0, y0))
	{
		return FONT_ERROR_OFF_SCREEN;
	}
	for (int i = 0; i < length; i++) {
		if (!(
				(
					font->glyph_start <= text[i] &&
					font->glyph_start + font->glyph_count > text[i]
				) ||
				(text[i] == FONT_LINE_FEED) ||
				(text[i] == FONT_CARRIAGE_RETURN)
			))
		{
			return FONT_ERROR_UNKNOWN_CHAR;
		}
	}
	
	s_coord_t x = x0;
	s_coord_t y = y0;
	for (int i = 0; i < length; i++) {
		if (text[i] == FONT_LINE_FEED)
		{
			y += font->line_height;
		}
		else if (text[i] == FONT_CARRIAGE_RETURN)
		{
			x = x0;
		}
		else
		{
			font_glyph_t * glyph = font->glyphs[text[i] - font->glyph_start];
			if (glyph == NULL)
			{
				glyph = &font_default_glyph;
			}

			screen_t glyph_inter = {
				glyph->width,
				glyph->height,
				glyph->pixels
			};
			
			if ((wrap_width > 0) && ((x + glyph->width) > x0 + wrap_width))
			{
				y += font->line_height;
				x = x0;
			}
			
			graphics_overlay_data(&glyph_inter, 0, 0, glyph->width,
					glyph->height, screen, x, y + glyph->y_offset);

			x += glyph->width + font->spacing;
		}
	}
	
	if (!SPIXEL_CHECK(screen, x - font->spacing, y + font->line_height - 1))
	{
		return FONT_ERROR_OFF_SCREEN_PARTIAL;
	}
	else
	{
		return FONT_ERROR_NONE;
	}
}

font_error_t
font_write_simple (char * text, screen_t * screen, s_coord_t x0, s_coord_t y0,
				   s_coord_t wrap_width)
{
	char processed[FONT_SIMPLE_MAX_LENGTH * 2] = { 0 };
	int length = 0;
	int i = 0;
	while ((text[i] != '\0') && (i <= FONT_SIMPLE_MAX_LENGTH))
	{
		if (text[i] == FONT_LINE_FEED || text[i] == FONT_CARRIAGE_RETURN)
		{
			processed[length] = FONT_CARRIAGE_RETURN;
			processed[length + 1] = FONT_LINE_FEED;
			i++;
			length += 2;
		}
		else
		{
			processed[length] = text[i];
			i++;
			length++;
		}
	}
	return font_write(&font_standard, processed, length, screen, x0, y0,
			wrap_width);
}
