#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/attribs.h>

#include "ports.h"
#include "leds.h"
#include "sw_timer.h"
#include "pmp_6800.h"
#include "ssd1305.h"

//----------------------------------------------------------
//                         BF1SEQ0
//----------------------------------------------------------
#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xFFFF

#define VirtAddr_TO_PhysAddr(v) ((unsigned long)(v) & 0x1FFFFFFF)


int main(void)
{
	// CPU Performance Optimization:
	register unsigned long tmp_cache;                 //KSEG0 cache enable
	asm("mfc0 %0,$16,0" :  "=r"(tmp_cache));
	tmp_cache = (tmp_cache & ~7) | 3;
	asm("mtc0 %0,$16,0" :: "r" (tmp_cache));
	
	PRECONbits.PFMWS=2;       //Flash wait states = 2 CPU clock cycles @ 200Mhz        
	PRECONbits.PREFEN = 2;    //Enable predictive prefetch for CPU instructions and CPU data
	PRISSbits.PRI7SS = 7;	//DMA Interrupt with priority level of 7 uses Shadow Set 7
	PRISSbits.PRI6SS = 6;	//Interrupt with priority level of 6 uses Shadow Set 6
	PRISSbits.PRI5SS = 5;	//Interrupt with priority level of 5 uses Shadow Set 5
	PRISSbits.PRI4SS = 4;	//Interrupt with priority level of 4 uses Shadow Set 4
	PRISSbits.PRI3SS = 3;	//Interrupt with priority level of 3 uses Shadow Set 3
	PRISSbits.PRI2SS = 2;	//Interrupt with priority level of 2 uses Shadow Set 2
	
	INTCONbits.MVEC = 1;	//Enable multi-vector interrupts
	__builtin_enable_interrupts(); // Global Interrupt Enable 
	
	ports_init();
	pmp_6800_init();
	ssd1305_init();
	init_sw_timer();

	sw_timer test1 = TIMER(1000);
	sw_timer test2 = TIMER(500);
	sw_timer test3 = TIMER(100);
    
	bool state = false;
    ssd1305_enable();
	
	
	while(1)
	{
		if (tmr_expired(test1)) {
			reset_timer(&test1);
			LED_Toggle(LED_1);
			
			if (state)
			{
				pmp_6800_write_command(0xA4);
				state = false;
			}
			else
			{
				pmp_6800_write_command(0xA5);
				state = true;
			}
		}
		if (tmr_expired(test2)) {
			reset_timer(&test2);
			LED_Toggle(LED_2);
		}
		if (tmr_expired(test3)) {
			reset_timer(&test3);
			
			uint8_t status = pmp_6800_read_status();
			if (status & 0b01000000)
			{
				LED_On(LED_3);
			}
			else
			{
				LED_Off(LED_3);
			}
		}
	}
}
