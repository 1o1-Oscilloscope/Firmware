/*
 * Graphical Oscilloscope Display
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   scope_display.c
 * 
 * @Summary
 *   Contains the glue logic to run the display for the oscilloscope.
*/

#include "scope_display.h"

#include <stdbool.h>
#include <stdint.h>

#include "common/screen.h"
#include "common/sw_timer.h"
#include "drivers/ssd1305.h"
#include "graphics/font.h"
#include "graphics/graphics.h"
#include "graphics/packed_graphics.h"

// Basic graphical objects
FULLSIZE_LAYER(l_grid);
FULLSIZE_LAYER(l_plot);
FULLSIZE_LAYER(m_toast);
FULLSIZE_LAYER(l_toast);
screen_t * layers[LAYER_COUNT] = {
	&l_grid,
	&l_plot,
	&m_toast,
	&l_toast
};
bool layer_is_mask[LAYER_COUNT] = {
	false,
	false,
	true,
	false
};
uint8_t output_values[XALG_COLUMNS][XALG_PAGES] = { 0 };
packed_graphics_t output = {
	XALG_COLUMNS,
	XALG_PAGES,
	(uint8_t *)output_values
};

sw_timer toast_timeout = TIMER(2500);
sw_timer splash_timeout = TIMER(1500);
bool update = false;


static void
display_layers ()
{
	graphics_pack_layers(layers, LAYER_COUNT, &output, layer_is_mask);
	ssd1305_write_all(&output);
}

static void
generate_grid (screen_t * layer)
{
	graphics_fill_screen(layer, false);
	graphics_dotted_line(layer, S_VECTOR(PIXELS_PER_DIV * 1, 0), layer->size.y,
			true,  4, true);
	graphics_dotted_line(layer, S_VECTOR(PIXELS_PER_DIV * 2, 0), layer->size.y,
			true,  4, true);
	graphics_dotted_line(layer, S_VECTOR(PIXELS_PER_DIV * 3, 0), layer->size.y,
			true,  2, true);
	graphics_dotted_line(layer, S_VECTOR(PIXELS_PER_DIV * 4, 0), layer->size.y,
			true,  4, true);
	graphics_dotted_line(layer, S_VECTOR(PIXELS_PER_DIV * 5, 0), layer->size.y,
			true,  4, true);
	graphics_dotted_line(layer, S_VECTOR(0, PIXELS_PER_DIV * 1), layer->size.x,
			false, 4, true);
	graphics_dotted_line(layer, S_VECTOR(0, PIXELS_PER_DIV * 2), layer->size.x,
			false, 2, true);
	graphics_dotted_line(layer, S_VECTOR(0, PIXELS_PER_DIV * 3), layer->size.x,
			false, 4, true);
}

void
sd_init ()
{
	ssd1305_write_all(&graphics_logo);
	sw_timer_reset(&splash_timeout);
	
	graphics_fill_screen(&l_grid, false);
	graphics_fill_screen(&l_plot, false);
	graphics_fill_screen(&m_toast, true);
	graphics_fill_screen(&l_toast, false);
}

void
sd_task ()
{	
	if (splash_timeout.running && !sw_timer_expired(splash_timeout))
	{
		return;
	}
	else if (splash_timeout.running)
	{
		splash_timeout.running = false;
		generate_grid(&l_grid);
		update = true;
	}
	
	if (sw_timer_expired(toast_timeout))
	{ // Toast already displayed, reset.
		graphics_fill_screen(&m_toast, true);
		graphics_fill_screen(&l_toast, false);
		update = true;

		toast_timeout.running = false;
	}
	
	if (update)
	{
		display_layers();
		update = false;
	}
}

void
sd_show_toast (char * text)
{
	char buffer[TOAST_MAX_LENGTH] = { 0 };
	unsigned int textlen = font_process_string(text, buffer, TOAST_MAX_LENGTH);
	s_vector_t text_size = { 0 };
	font_error_t error = font_size(&font_standard, buffer, textlen,
			m_toast.size.x - 16, &text_size);
	text_size = S_VECTOR_SUB(text_size, S_VECTOR(1, 3));
	
	if ((error != FONT_ERROR_NONE) || (text_size.y > (m_toast.size.y - 16)))
	{ // Text invalid
		return;
	}
	
	const s_coord_t padding = 3;
	const s_coord_t border = 2;
	const s_coord_t margin_bottom = 6;
	s_coord_t x_center = m_toast.size.x / 2;
	s_vector_t outline = S_VECTOR_MUL(S_VECTOR_ONE, padding + border);
	s_vector_t size = S_VECTOR_ADD(text_size, S_VECTOR_MUL(outline, 2));
	s_vector_t topleft = S_VECTOR(x_center - size.x / 2,\
		m_toast.size.y - size.y - margin_bottom);
	
	graphics_fill_screen(&m_toast, true);
	graphics_fill_screen(&l_toast, false);
	graphics_fill_rect(&m_toast, topleft, S_VECTOR_ADD(topleft, size), false);
	graphics_draw_rect(&l_toast, S_VECTOR_ADD(topleft, S_VECTOR_ONE),
			S_VECTOR_SUB(S_VECTOR_ADD(topleft, size), S_VECTOR_ONE), true);
	font_write(&font_standard, buffer, textlen, &l_toast,
			S_VECTOR_ADD(topleft, outline), m_toast.size.x - 16, false);
	update = true;
	
	sw_timer_reset(&toast_timeout);
}

void
sd_plot_data (uint8_t * buffer, uint8_t size)
{
	graphics_fill_screen(&l_plot, false);
	s_coord_t y_max = l_plot.size.y - 1;
	for (uint8_t i = 0; i < SMIN(size - 1, l_plot.size.x - 1); i++)
	{
		graphics_draw_line(
			&l_plot,
			S_VECTOR(i,     y_max - SMIN(buffer[i],     y_max)),
			S_VECTOR(i + 1, y_max - SMIN(buffer[i + 1], y_max)),
			true
		);
	}
	update = true;
}
