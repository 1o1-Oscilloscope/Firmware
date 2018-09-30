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
 *   This revision defines a monochrome color model.
*/

#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


#define S_PIXEL_MAX 1
#define SPIXEL(screen, x0, y0) *((screen)->pixels +\
		(x0) * (screen)->size.y + (y0))
#define S_COORD_CHECK(screen, x0, y0) ((s_coord_t)(x0) >= 0 &&\
		(s_coord_t)(x0) < (screen)->size.x &&\
		(s_coord_t)(y0) >= 0 &&\
		(s_coord_t)(y0) < (screen)->size.y)

#define S_VECTOR(x, y) (s_vector_t){(x), (y)}
#define S_VECTOR_ZERO S_VECTOR(0, 0)
#define S_VECTOR_UX S_VECTOR(1, 0)
#define S_VECTOR_UY S_VECTOR(0, 1)
#define S_VECTOR_ONE S_VECTOR(1, 1)
#define SPIXEL_V(screen, v) *((screen)->pixels +\
		(v).x * (screen)->size.y + (v).y)
#define S_VECTOR_CHECK(screen, v) ((v).x >= 0 &&\
		(v).x < (screen)->size.x &&\
		(v).y >= 0 &&\
		(v).y < (screen)->size.y)
#define S_VECTOR_ADD(v0, v1) (s_vector_t){(v0).x + (v1).x, (v0).y + (v1).y}
#define S_VECTOR_SUB(v0, v1) (s_vector_t){(v0).x - (v1).x, (v0).y - (v1).y}
#define S_VECTOR_MUL(v, k) (s_vector_t){(v).x * (k), (v).y * (k)}

#define SMAX(a, b)  (((a) > (b)) ? (a) : (b))
#define SMIN(a, b)  (((a) < (b)) ? (a) : (b))

#ifdef	__cplusplus
extern "C"
{
#endif


typedef bool s_pixel_t;
typedef int16_t s_coord_t;


typedef struct
{
	s_coord_t x;
	s_coord_t y;
} s_vector_t;

typedef struct
{
	s_vector_t size;
	s_pixel_t * pixels;
} screen_t;


#ifdef	__cplusplus
}
#endif

#endif /* SCREEN_H */
