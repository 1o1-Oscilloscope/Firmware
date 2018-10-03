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


#define BUTTON_COUNT 6


#ifdef	__cplusplus
extern "C"
{
#endif


typedef enum {
    BUTTON_1 = 0,
	BUTTON_2 = 1,
	BUTTON_3 = 2,
	BUTTON_4 = 3,
	BUTTON_5 = 4,
	BUTTON_6 = 5
} button_t;


bool button_read (button_t button);

void button_task    ();
bool button_pressed (button_t button);


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */
