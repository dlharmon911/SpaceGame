#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_stats.h"

static const s_point_t s_line_offset = { 0.5f, 0.5f };
static const float s_line_spacing = 9.0f;
static const ALLEGRO_COLOR s_color = { 1.0f, 1.0f, 1.0f, 1.0f };

static void g_stats_draw_line(const ALLEGRO_FONT* font, float x, float y, int32_t* line, const char* const format, ...)
{
	static va_list va_arg_list;
	static char buffer[2048];

	buffer[0] = 0;

	va_start(va_arg_list, format);
	vsnprintf(buffer, 2048, format, va_arg_list);
	va_end(va_arg_list);

	al_draw_text(font, s_color, x + s_line_offset.m_x, y + s_line_offset.m_y + s_line_spacing * (float)(*line), 0, buffer);

	(*line) = (*line) + 1;
}

void g_stats_draw(const ALLEGRO_FONT* font, const g_stats_t* stats, float x, float y)
{
	int32_t line = 0;

	g_stats_draw_line(font, x, y, &line, "Display Size: (%d, %d)", (int32_t)stats->m_display_size.m_x, (int32_t)stats->m_display_size.m_y);
	g_stats_draw_line(font, x, y, &line, "FPS :%.2lf", stats->m_fps);
	g_stats_draw_line(font, x, y, &line, "Ship Position : (%d, %d)", (int32_t)stats->m_ship_position->m_x, (int32_t)stats->m_ship_position->m_y);
	g_stats_draw_line(font, x, y, &line, "Star Count : %d", stats->m_star_count);
	g_stats_draw_line(font, x, y, &line, "Boulder Count : %d (%d)", stats->m_boulder_count, stats->m_boulder_capacity);
}

void g_stats_zero_initialize_data(g_stats_t* stats)
{
	if (!stats)
	{
		return;
	}

	s_point_set_zero(&stats->m_display_size);
	stats->m_star_count = 0;
	stats->m_boulder_count = 0;
	stats->m_boulder_capacity = 0;
	stats->m_ship_position = NULL;
	stats->m_fps = 0.0;
}
