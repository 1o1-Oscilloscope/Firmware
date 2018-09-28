/*
 * Software Timer Library
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   sw_timer.h
 * 
 * @Summary
 *   Provides simple configurable timers backed by a single hardware timer.
*/

#ifndef SW_TIMER_H
#define	SW_TIMER_H

#include <stdbool.h>
#include <stdint.h>

#define TIMER(LEN) {0, LEN, true};

#ifdef	__cplusplus
extern "C"
{
#endif


extern uint32_t g_ticks;

typedef struct
{
    uint32_t start_tick;
    uint32_t length;
    bool running;
} sw_timer;


void sw_timer_init(void);
bool sw_timer_expired(sw_timer timer);
void sw_timer_reset(sw_timer* timer);


#ifdef	__cplusplus
}
#endif

#endif	/* SW_TIMER_H */
