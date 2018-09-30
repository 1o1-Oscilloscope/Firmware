/*
 * Solomon Systech SSD1305 Interface
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   ssd1305.c
 * 
 * @Summary
 *   Interface to control SSD1305 based OLED display. Written for Electronic
 *   Assembly GmbH EA W096064-XALG display on 1o1 v1.0 board.
*/

#include "ssd1305.h"

#include <stdint.h>

#include "../ports.h"
#include "../common/sw_timer.h"
#include "../common/screen.h"
#include "../drivers/pmp_6800.h"
#include "../graphics/packed_graphics.h"


void
ssd1305_enable ()
{
	OLED_RES_LAT = PIN_ON;
	sw_timer wait_init = TIMER(3);
	while (!sw_timer_expired(wait_init)) {}
	
	pmp_6800_write_command(0x40);
	pmp_6800_write_command(0xA6);
	pmp_6800_write_command(0x81);
	pmp_6800_write_command(0x7F);
	pmp_6800_write_command(0xD5);
	pmp_6800_write_command(0x40);
	pmp_6800_write_command(0xD9);
	pmp_6800_write_command(0x44);
	pmp_6800_write_command(0xA1);
	pmp_6800_write_command(0xC8);
	pmp_6800_write_command(0xAF);
}

void
ssd1305_disable ()
{
	OLED_RES_LAT = PIN_OFF;
}

static void
ssd1305_gddr_setup_block (uint8_t c0, uint8_t c1, uint8_t p0, uint8_t p1)
{
	pmp_6800_write_command(0x20);
	pmp_6800_write_command(0x01);
	pmp_6800_write_command(0x21);
	pmp_6800_write_command(c0);
	pmp_6800_write_command(c1);
	pmp_6800_write_command(0x22);
	pmp_6800_write_command(p0);
	pmp_6800_write_command(p1);
}

static void
ssd1305_gddr_setup_full ()
{
	ssd1305_gddr_setup_block(
		XALG_START_COLUMN,
		XALG_END_COLUMN,
		XALG_START_PAGE,
		XALG_END_PAGE
	);
}

void
ssd1305_clear ()
{
	ssd1305_gddr_setup_full();
	
	uint8_t page, column;
	for (column = XALG_START_COLUMN; column <= XALG_END_COLUMN; column++)
	{
		for (page = XALG_START_PAGE; page <= XALG_END_PAGE; page++)
		{
			pmp_6800_write_data(0);
		}
	}
}

void
ssd1305_write_all (packed_graphics_t * graphics)
{
	ssd1305_gddr_setup_full();
	
	if ((XALG_COLUMNS != graphics->columns) || (XALG_PAGES != graphics->pages))
	{
		return;
	}
	
	uint8_t page, column;
	for (column = 0; column < XALG_COLUMNS; column++)
	{
		for (page = 0; page < XALG_PAGES; page++)
		{
			pmp_6800_write_data(graphics->bytes[column * XALG_PAGES + page]);
		}
	}
}

void
ssd1305_write_all_screen (screen_t * screen)
{
	ssd1305_gddr_setup_full();
	
	if ((XALG_COLUMNS != screen->size.x) || (XALG_ROWS != screen->size.y))
	{
		return;
	}
	
	for (uint8_t column = 0; column < XALG_COLUMNS; column++)
	{
		for (uint8_t page = 0; page < XALG_PAGES; page++)
		{
			uint8_t byte = 0;
			for (uint8_t ibit = 0; ibit < 8; ibit++)
			{
				if(SPIXEL(screen, column, page * 8 + ibit))
				{
					byte += 1 << ibit;
				}
			}
			pmp_6800_write_data(byte);
		}
	}
}
