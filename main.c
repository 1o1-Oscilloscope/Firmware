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
#include <stdio.h>
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

#define UI_TRIGGER_MAX 63
#define UI_TIMEDIV_MAX 213


static void ui_cycle_gain     ();
static void ui_oneshot_toggle ();
static void ui_trigger_up     ();
static void ui_trigger_down   ();
static void ui_trigger_toast  ();
static void ui_timediv_up     ();
static void ui_timediv_down   ();
static void ui_timediv_toast  ();


static afe_gain_t ui_gain_state    = GAIN_0_1;
static bool       ui_oneshot_state = false;
static bool       ui_oneshot_done  = false;
static uint8_t    ui_trigger_state = 32;
static uint32_t   ui_timediv_state = 25;


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
	
	adc_set_trigger_level(ui_trigger_state);
	afe_gain_set(ui_gain_state);
	
	while(1)
	{		
		// Button input handling
		if (sw_timer_expired(input_timer))
		{
			sw_timer_reset(&input_timer);
			button_task();
			
			if (button_pressed(BUTTON_1))
			{
				ui_cycle_gain();
			}
			if (button_pressed(BUTTON_2))
			{
				ui_oneshot_toggle();
			}
			if (button_pressed(BUTTON_3))
			{
				ui_timediv_up();
			}
			if (button_pressed(BUTTON_4))
			{
				ui_timediv_down();
			}
			if (button_pressed(BUTTON_5))
			{
				ui_trigger_down();
			}
			if (button_pressed(BUTTON_6))
			{
				ui_trigger_up();
			}
		}
		
		// Update Display
		if (sw_timer_expired(scope_timer))
		{
			sw_timer_reset(&scope_timer);
			
			if (!(ui_oneshot_state && ui_oneshot_done))
			{
				uint8_t buff[96] = { 0 };
				if (adc_get_data(buff, ui_timediv_state))
				{
					sd_plot_data(buff, 96);
					adc_reset_trigger();
					led_toggle(LED_3);
					ui_oneshot_done = true;
				}
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

static void
ui_cycle_gain ()
{
	switch (ui_gain_state)
	{
		case GAIN_1:
			ui_gain_state = GAIN_0_5;
			sd_show_toast("1.6 V/div");
			break;

		case GAIN_0_5:
			ui_gain_state = GAIN_0_1;
			sd_show_toast("8.0 V/div");
			break;

		case GAIN_0_1:
		default:
			ui_gain_state = GAIN_1;
			sd_show_toast("0.8 V/div");
			break;
	}
	afe_gain_set(ui_gain_state);
}

static void
ui_oneshot_toggle ()
{
	if (ui_oneshot_state)
	{
		ui_oneshot_state = false;
		sd_show_toast("Auto Trigger");
	}
	else
	{
		ui_oneshot_state = true;
		ui_oneshot_done  = false;
		sd_show_toast("One-Shot");
	}
}

static void
ui_trigger_up ()
{
	if (ui_trigger_state < UI_TRIGGER_MAX)
	{
		ui_trigger_state++;
	}
	
	adc_set_trigger_level(ui_trigger_state);
	ui_trigger_toast();
}

static void
ui_trigger_down ()
{
	
	if (ui_trigger_state > 0)
	{
		ui_trigger_state--;
	}
	
	adc_set_trigger_level(ui_trigger_state);
	ui_trigger_toast();
}

static void
ui_trigger_toast ()
{
	float volts = (float)(ui_trigger_state - 2 * PIXELS_PER_DIV) /
			(float)PIXELS_PER_DIV * 0.8f;
	char message[20] = { 0 };
	
	switch (ui_gain_state)
	{
		case GAIN_0_5:
			volts *= 0.5f;
			break;

		case GAIN_0_1:
			volts *= 0.1f;
			break;
		
		default:
			break;
	}
	
	snprintf(message, 19, "Trigger: %.2f V", volts);
	sd_show_toast(message);
}

static void
ui_timediv_up ()
{
	if (ui_timediv_state < UI_TIMEDIV_MAX)
	{
		ui_timediv_state++;
	}
	
	ui_timediv_toast();
}

static void
ui_timediv_down ()
{
	
	if (ui_timediv_state > 0)
	{
		ui_timediv_state--;
	}
	
	ui_timediv_toast();
}

static void
ui_timediv_toast ()
{
	float seconds = (float)(ui_timediv_state * PIXELS_PER_DIV) / 10000000.0f;
	char message[20] = { 0 };
	
	if (seconds < 0.001)
	{
		snprintf(message, 19, "%.1f us/div", seconds * 1000000);
	}
	else
	{
		snprintf(message, 19, "%.1f ms/div", seconds * 1000);
	}
	
	sd_show_toast(message);
}
