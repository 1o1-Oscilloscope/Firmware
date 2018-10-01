/*
 * Analog Subsystem Test/Development Driver
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   as_test.h
 * 
 * @Summary
 *   Dummy analog subsystem with correct interface. For developing UI.
*/

#include "as_test.h"

#include <math.h>
#include <stdint.h>

void
ast_fill_sine (uint8_t * buffer, uint8_t length, float period,
			   uint8_t amplitude, uint8_t offset)
{
	for (uint8_t i = 0; i < length; i++)
	{
		buffer[i] = amplitude * sinf((float) i * 2.0f * (float)M_PI / period)\
			+ offset;
	}
}
