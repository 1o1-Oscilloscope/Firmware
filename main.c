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
#include "graphics/font.h"

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
	screen_t layer1 = {
		S_VECTOR(XALG_COLUMNS, XALG_ROWS),
		(s_pixel_t *)layer1_values
	};
	s_pixel_t layer2_values[XALG_COLUMNS][XALG_ROWS] = { 0 };
	screen_t layer2 = {
		S_VECTOR(XALG_COLUMNS, XALG_ROWS),
		(s_pixel_t *)layer2_values
	};
	screen_t * layers[LAYER_COUNT] = {
		&layer1,
		&layer2
	};
	bool layer_is_mask[LAYER_COUNT] = {
		false,
		true
	};
	uint8_t output_values[XALG_COLUMNS][XALG_PAGES] = { 0 };
	packed_graphics_t output = {
		XALG_COLUMNS,
		XALG_PAGES,
		(uint8_t *)output_values
	};
	
	// Set up screen and display flash
    ssd1305_enable();
    ssd1305_clear();
	ssd1305_write_all(&graphics_logo);
	sw_timer splash_timeout = TIMER(1500);
	
	while(1)
	{
		// Blink LED
		if (sw_timer_expired(test2))
		{
			sw_timer_reset(&test2);
			LED_Toggle(LED_2);
		}
		
		// Graphics test/example (one-shot))
		if (sw_timer_expired(splash_timeout))
		{
			splash_timeout.running = false;
			
			// Draw test graphical elements
			font_write_simple("This is Text",
					&layer1, S_VECTOR(1, 1), 0, false);
			graphics_fill_rect(&layer1, S_VECTOR(0, 11),
					S_VECTOR(layer1.size.x - 1, 21), true);
			font_write_simple("This is Inverted Text",
					&layer1, S_VECTOR(1, 12), 0, true);
			graphics_draw_rect(&layer1, S_VECTOR(32, 27),
					S_VECTOR(61, 56), true);
			graphics_fill_rect(&layer1, S_VECTOR(35, 30),
					S_VECTOR(58, 53), true);
			graphics_draw_line(&layer1, S_VECTOR(33, 28),
					S_VECTOR(60, 55), false);
			graphics_dotted_line(&layer1, S_VECTOR( 5, 27), 30, true, 1, true);
			graphics_dotted_line(&layer1, S_VECTOR(10, 27), 30, true, 2, true);
			graphics_dotted_line(&layer1, S_VECTOR(15, 27), 30, true, 3, true);
			graphics_dotted_line(&layer1, S_VECTOR(20, 27), 30, true, 4, true);
			graphics_dotted_line(&layer1, S_VECTOR(25, 27), 30, true, 5, true);
			
			// Test mask
			graphics_fill_rect(&layer2, S_VECTOR_ZERO,
					S_VECTOR_SUB(layer2.size, S_VECTOR_ONE), true);
			graphics_fill_rect(&layer2, S_VECTOR(48, 36), S_VECTOR(95, 47),
					false);
			
			// Display layers
			graphics_pack_layers(layers, LAYER_COUNT, &output, layer_is_mask);
			ssd1305_write_all(&output);
		}
	}
}
