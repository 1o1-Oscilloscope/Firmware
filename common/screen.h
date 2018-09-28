/*
 * Common Screen Interface (Greyscale)
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   screen.h
 * 
 * @Summary
 *   Provides a standard screen/framebuffer interface.
 *   This revision implements a monochrome color model.
*/

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


#define S_PIXEL_MAX 1
#define SPIXEL(screen, x, y) *(((screen)->pixels) + (x) * (screen)->height + (y))
#define SPIXEL_CHECK(screen, x, y) ((uint16_t)(x) >= 0 && (uint16_t)(x) < (screen)->width && (uint16_t)(y) >= 0 && (uint16_t)(y) < (screen)->height)

#define SMAX(a, b)  (((a) > (b)) ? (a) : (b))
#define SMIN(a, b)  (((a) < (b)) ? (a) : (b))

#ifdef	__cplusplus
extern "C"
{
#endif


typedef bool s_pixel_t;
typedef uint8_t s_coord_t;


typedef struct
{
	s_coord_t  width;
	s_coord_t  height;
	s_pixel_t * pixels;
} screen_t;

s_pixel_t s_compositef (s_pixel_t bottom, s_pixel_t top, float alpha);
bool s_validate_coords (screen_t * screen, s_coord_t x, s_coord_t y);


#ifdef	__cplusplus
}
#endif

#endif /* SCREEN_H */
