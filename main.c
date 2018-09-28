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
#include "leds.h"
#include "common/sw_timer.h"
#include "common/screen.h"
#include "drivers/pmp_6800.h"
#include "drivers/ssd1305.h"
#include "graphics/packed_graphics.h"
#include "graphics/graphics.h"

// BF1SEQ0
#pragma config TSEQ =       0x0000
#pragma config CSEQ =       0xFFFF

#define VirtAddr_TO_PhysAddr(v) ((unsigned long)(v) & 0x1FFFFFFF)

#define LAYER_COUNT 2
#define DEG2RADF(d) ((float)(d) / 180.0f * (float)M_PI)


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
	pmp_6800_init();
	ssd1305_init();
	sw_timer_init();
	
	// Timers to blink LEDs with
	sw_timer test1 = TIMER(1000);
	sw_timer test2 = TIMER(500);
	sw_timer test3 = TIMER(100);
    
	// Set up graphics objects
	s_pixel_t layer1_values[XALG_COLUMNS][XALG_ROWS] = { 0 };
	screen_t layer1 = { XALG_COLUMNS, XALG_ROWS, (s_pixel_t *)layer1_values };
	s_pixel_t layer2_values[XALG_COLUMNS][XALG_ROWS] = { 0 };
	screen_t layer2 = { XALG_COLUMNS, XALG_ROWS, (s_pixel_t *)layer2_values };
	screen_t * layers[LAYER_COUNT] = { &layer1, &layer2 };
	uint8_t output_values[XALG_COLUMNS][XALG_PAGES] = { 0 };
	packed_graphics_t output = { XALG_COLUMNS, XALG_PAGES, (uint8_t *)output_values };
	
	// Set up screen and display flash
    ssd1305_enable();
    ssd1305_clear();
	ssd1305_write_all(&graphics_logo);
	sw_timer splash_timeout = TIMER(1500);
	int lpos = 0;
	
	while(1)
	{
		// Blink LEDs
		if (sw_timer_expired(test1))
		{
			sw_timer_reset(&test1);
			LED_Toggle(LED_1);
		}
		if (sw_timer_expired(test2))
		{
			sw_timer_reset(&test2);
			LED_Toggle(LED_2);
		}
		if (sw_timer_expired(test3))
		{
			sw_timer_reset(&test3);
			LED_Toggle(LED_3);
		}
		
		// Graphics test/example
		if (sw_timer_expired(splash_timeout))
		{
			sw_timer_reset(&splash_timeout);
			
			if (splash_timeout.length > 33)
			{
				// First run, draw some basic geometry and update timer to 30Hz
				splash_timeout.length = 33;
				graphics_draw_rect(&layer1,  0,  0, 20, 20, 1);
				graphics_draw_line(&layer1, 20, 20, 60, 20, 1);
				graphics_draw_line(&layer1, 20, 20, 60, 40, 1);
				graphics_draw_line(&layer1, 20, 20, 60, 60, 1);
				graphics_draw_line(&layer1, 20, 20, 40, 60, 1);
				graphics_draw_line(&layer1, 20, 20, 20, 60, 1);
			}
			
			// Draw pivoting line
			graphics_draw_rect(&layer2, 20, 20, 60, 60, 0);
			float angle = (sinf(DEG2RADF(lpos)) + 1) * (float)M_PI_4;
			s_coord_t x = (s_coord_t)floorf(40.0f * sinf(angle) + 0.5f);
			s_coord_t y = (s_coord_t)floorf(40.0f * cosf(angle) + 0.5f);
			graphics_draw_line(&layer2, 20, 20, 20 + x, 20 + y, 1);
			lpos += 3;
			
			// Display layers
			graphics_pack_layers(layers, LAYER_COUNT, &output, NULL);
			ssd1305_write_all(&output);
		}
	}
}
