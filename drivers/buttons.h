/*
 * 1o1 Buttons Driver
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   buttons.h
 * 
 * @Summary
 *   Interface to the buttons on the 1o1 board.
*/

#ifndef BUTTONS_H
#define	BUTTONS_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C"
{
#endif


typedef enum {
    BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_4,
	BUTTON_5,
	BUTTON_6,
} button_t;


bool button_read (button_t button);


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */
