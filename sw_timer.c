#include <stdlib.h>
#include <limits.h>

#include <sys/attribs.h>
#include <xc.h>

#include "sw_timer.h"

uint32_t ticks;

void init_sw_timer(void){
    IEC1bits.T8IE = 0;   // Disable timer int
    
    TMR8 = 0;            // Clear Timer
    PR8 = 50000;         // 1ms period
    T8CONbits.T32 = 0;   // 16 bit timers
    T8CONbits.TCKPS = 1; // 1:2 prescale value
    T8CONbits.TGATE = 0; // Gated time accumulation is disabled
    T8CONbits.TCS = 0;   // Internal peripheral clock
    T8CONbits.SIDL = 0;  // Stop in idle mode
    
    IPC9bits.T8IP = 5; // Interrupt priority
    IPC9bits.T8IS = 0; // Sub-priority
    
    T8CONbits.ON = 1;    // Enable Timer
    
    IFS1bits.T8IF = 0;   // Clear int
    IEC1bits.T8IE = 1;   // Enable timer int
    
    ticks++;
}

uint32_t tmr_elapsed(sw_timer timer){
    // On the PIC32MZ this is atomic
    uint32_t local_ticks = ticks;
    
    if (local_ticks >= timer.start_tick){
        return local_ticks - timer.start_tick;
    } else {
        return UINT32_MAX - timer.start_tick - local_ticks;
    }
}

bool tmr_expired(sw_timer timer){
    if (timer.running != true){
        return false;
    }
    
    return tmr_elapsed(timer) > timer.length;
}

void reset_timer(sw_timer* timer){
    // On the PIC32MZ this is atomic
    uint32_t local_ticks = ticks;
    
    timer->start_tick = local_ticks;
}

void __ISR(_TIMER_8_VECTOR, IPL5SRS) T8Interrupt(void){
    IFS1bits.T8IF = 0;
	ticks++;
}
