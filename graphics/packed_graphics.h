/*
 * Packed Graphics Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   packed_graphics.h
 * 
 * @Summary
 *   Provides a standard interface for byte-packed monochrome graphics.
*/

#ifndef PACKED_GRAPHICS_H
#define	PACKED_GRAPHICS_H

#include <stdint.h>

#define PGPIXEL(pg, col, page) *(((pg)->bytes) + (col) * (pg)->pages + (page))
#define PGPIXEL_CHECK(pg, x, y) \
((uint8_t)(col) >= 0 &&\
 (uint8_t)(col) < (pg)->columns &&\
 (uint8_t)(page) >= 0 &&\
 (uint8_t)(page) < (pg)->pages\
)

#ifdef	__cplusplus
extern "C"
{
#endif


typedef struct
{
	uint8_t columns;
	uint8_t pages;
	uint8_t * bytes;
} packed_graphics_t;

extern packed_graphics_t graphics_logo;


#ifdef	__cplusplus
}
#endif

#endif	/* PACKED_GRAPHICS_H */

