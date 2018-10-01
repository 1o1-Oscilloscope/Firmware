/*
 * 1o1 Oscilloscope Firmware
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   main.c
 * 
 * @Summary
 *   Contains initialization and main task loop for 1o1 Oscilloscope.
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <math.h>

#include "ports.h"
#include "scope_display.h"
#include "common/sw_timer.h"
#include "common/screen.h"
#include "drivers/pmp_6800.h"
#include "drivers/ssd1305.h"
#include "drivers/buttons.h"
#include "drivers/leds.h"
#include "drivers/as_test.h"
#include "drivers/adc.h"
#include "drivers/afe_gain.h"
#include "graphics/packed_graphics.h"
#include "graphics/graphics.h"
#include "graphics/font.h"

// BF1SEQ0
#pragma config TSEQ = 0x0000
#pragma config CSEQ = 0xFFFF


int main(void)
{
	// CPU Performance Optimization:
	register unsigned long tmp_cache;                 //KSEG0 cache enable
	__asm__("mfc0 %0,$16,0" :  "=r"(tmp_cache));
	tmp_cache = (tmp_cache & ~7) | 3;
	__asm__("mtc0 %0,$16,0" :: "r" (tmp_cache));
	PRECONbits.PFMWS=2;       //Flash wait states = 2 CPU clock cycles @ 200Mhz        
	PRECONbits.PREFEN = 2;    //Enable predictive prefetch for CPU instructions and CPU data
	
	// Interrupt setup
	PRISSbits.PRI7SS = 7;	//DMA Interrupt with priority level of 7 uses Shadow Set 7
	PRISSbits.PRI6SS = 6;	//Interrupt with priority level of 6 uses Shadow Set 6
	PRISSbits.PRI5SS = 5;	//Interrupt with priority level of 5 uses Shadow Set 5
	PRISSbits.PRI4SS = 4;	//Interrupt with priority level of 4 uses Shadow Set 4
	PRISSbits.PRI3SS = 3;	//Interrupt with priority level of 3 uses Shadow Set 3
	PRISSbits.PRI2SS = 2;	//Interrupt with priority level of 2 uses Shadow Set 2
	INTCONbits.MVEC = 1;	//Enable multi-vector interrupts
	__builtin_enable_interrupts(); // Global Interrupt Enable 
	
	// Subsystem initialization
	ports_init();
	sw_timer_init();
	pmp_6800_init();
    ssd1305_init();
	sd_init();
	adc_init();
	
	// Timers
	sw_timer blink_timer = TIMER(500);
	sw_timer input_timer = TIMER(10);
	sw_timer scope_timer = TIMER(50);
	sw_timer_reset(&blink_timer);
	sw_timer_reset(&input_timer);
	sw_timer_reset(&scope_timer);
	
	bool button1_state = false;
	
	uint8_t sin_buf[96] = { 0 };
	ast_fill_sine(sin_buf, 96, 20.0f, 24, 32);
	sd_plot_data(sin_buf, 96);
	
	adc_set_trigger_level(32);
	afe_gain_t gain_state = GAIN_0_1;
	afe_gain_set(gain_state);
	
	while(1)
	{		
		// Button input handling (temporary)
		if (sw_timer_expired(input_timer))
		{
			sw_timer_reset(&input_timer);
			if (input_timer.length > 50)
			{
				input_timer.length = 50;
			}
			
			if (!button1_state && button_read(BUTTON_1))
			{ // Button Rising Edge - Change Gain
				switch (gain_state)
				{
					case GAIN_1:
						gain_state = GAIN_0_5;
						sd_show_toast("Gain: 0.5");
						break;
					
					case GAIN_0_5:
						gain_state = GAIN_0_1;
						sd_show_toast("Gain: 0.1");
						break;
					
					case GAIN_0_1:
					default:
						gain_state = GAIN_1;
						sd_show_toast("Gain: 1.0");
						break;
				}
				afe_gain_set(gain_state);
				
				button1_state = true;
				led_on(LED_1);
			}
			else if (button1_state && !button_read(BUTTON_1))
			{ // Button Falling Edge
				button1_state = false;
				led_off(LED_1);
			}
		}
		
		// Update Display
		if (sw_timer_expired(scope_timer))
		{
			sw_timer_reset(&scope_timer);
			uint8_t buff[96] = { 0 };
			if (adc_get_data(buff, 25))
			{
				sd_plot_data(buff, 96);
				adc_reset_trigger();
				led_toggle(LED_3);
			}
			sd_task();
		}
		
		// Blink LED
		if (sw_timer_expired(blink_timer))
		{
			sw_timer_reset(&blink_timer);
			led_toggle(LED_2);
		}
	}
}
