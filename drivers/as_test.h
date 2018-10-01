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

#ifndef AS_TEST_H
#define	AS_TEST_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


void ast_fill_sine (uint8_t * buffer, uint8_t length, float period,
					uint8_t amplitude, uint8_t offset);


#ifdef	__cplusplus
}
#endif

#endif	/* AS_TEST_H */
