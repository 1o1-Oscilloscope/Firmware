/*
 * Raster Font Module
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   font.h
 * 
 * @Summary
 *   Provides font and glyph interfaces and drawing functions.
*/

#ifndef FONT_H
#define	FONT_H

#include "../common/screen.h"

#define FONT_ASCII_START     32
#define FONT_ASCII_COUNT     95
#define FONT_LINE_FEED       10
#define FONT_CARRIAGE_RETURN 13
#define FONT_SIMPLE_MAX_LENGTH 120

#ifdef	__cplusplus
extern "C"
{
#endif


typedef enum
{
	FONT_CHARSET_ASCII = 0
} font_charset_t;

typedef enum
{
	FONT_ERROR_NONE = 0,
	FONT_ERROR_UNKNOWN_CHAR,
	FONT_ERROR_OFF_SCREEN,
	FONT_ERROR_OFF_SCREEN_PARTIAL,
} font_error_t;

typedef struct
{
	s_coord_t width;
	s_coord_t height;
	s_coord_t y_offset;
	s_pixel_t * pixels;
} font_glyph_t;

typedef struct
{
	s_coord_t line_height;
	s_coord_t spacing;
	font_charset_t charset;
	uint32_t glyph_start;
	uint32_t glyph_count;
	font_glyph_t ** glyphs;
} font_t;


extern font_t font_standard;
extern font_glyph_t font_default_glyph;


font_error_t font_write        (font_t * font, char * text, int length,
								screen_t * screen, s_vector_t origin,
								s_coord_t wrap_width, bool invert);
font_error_t font_write_simple (char * text, screen_t * screen,
								s_vector_t origin, s_coord_t wrap_width,
								bool invert);


#ifdef	__cplusplus
}
#endif

#endif	/* FONT_H */

