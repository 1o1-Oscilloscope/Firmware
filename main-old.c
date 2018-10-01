/*
 * File:   main.c
 * Author: mark omo
 *
 * Created on February 28, 2018, 11:03 PM
 */

#include <stdbool.h>
#include <xc.h>

#include "sw_timer.h"
#include "gain_set.h"
#include "ports.h"
#include "leds.h"
#include "ADC.h"

void proc_setup(void) {
	register unsigned long tmp_cache; //KSEG0 cache enable
	asm("mfc0 %0,$16,0" : "=r"(tmp_cache));
	tmp_cache = (tmp_cache & ~7) | 3;
	asm("mtc0 %0,$16,0" ::"r" (tmp_cache));

	PRECONbits.PFMWS = 2; //Flash wait states = 2 CPU clock cycles @ 200Mhz        
	PRECONbits.PREFEN = 2; //Enable predictive prefetch for CPU instructions and CPU data
	PRISSbits.PRI7SS = 7; //DMA Interrupt with priority level of 7 uses Shadow Set 7
	PRISSbits.PRI6SS = 6; //Interrupt with priority level of 6 uses Shadow Set 6
	PRISSbits.PRI5SS = 5; //Interrupt with priority level of 5 uses Shadow Set 5
	PRISSbits.PRI4SS = 4; //Interrupt with priority level of 4 uses Shadow Set 4
	PRISSbits.PRI3SS = 3; //Interrupt with priority level of 3 uses Shadow Set 3
	PRISSbits.PRI2SS = 2; //Interrupt with priority level of 2 uses Shadow Set 2

	INTCONbits.MVEC = 1; //Enable multi-vector interrupts
	INTCONSET = _INTCON_MVEC_MASK;
	__builtin_enable_interrupts();
}

int main(void) {
	proc_setup();
	ports_init();
	init_sw_timer();    
	init_ADC();
	
    set_trig_level(32);
    
	Gain_Set(GAIN_0_1);

	sw_timer test1 = TIMER(1000);
	sw_timer test2 = TIMER(500);
	sw_timer test3 = TIMER(250);

	ANSELG = 0;

    uint8_t output_buff[96];
    
	while (1) {
		if (tmr_expired(test1)) {
			reset_timer(&test1);
			LED_Toggle(LED_1);
		}
		if (tmr_expired(test2)) {
			reset_timer(&test2);
			LED_Toggle(LED_2);
		}
		if (tmr_expired(test3)) {
			reset_timer(&test3);
			LED_Toggle(LED_3);
		}
		
		
		if(data_ready == true)
        {
            // 63 = 100us/div
            // 3 = 5us/div
            // 6 = 10us/div
            // 12 = 20us/div
            
            get_adc_data(output_buff, 25);
            reset_trigger();
        }
	}
}
