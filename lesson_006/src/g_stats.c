#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_stats.h"

static const s_point_t S_STATS_LINE_OFFSET = { 0.5f, 0.5f };
static const float S_STATS_LINE_SPACING = 9.0f;
static const ALLEGRO_COLOR S_STATS_COLOR = { 1.0f, 1.0f, 1.0f };

static void g_stats_draw_line(const ALLEGRO_FONT* font, float x, float y, int32_t* line, const char* const format, ...)
{
	static va_list va_arg_list;
	static char buffer[2048];

	buffer[0] = 0;

	va_start(va_arg_list, format);
	vsnprintf(buffer, 2048, format, va_arg_list);
	va_end(va_arg_list);

	al_draw_text(font, S_STATS_COLOR, x + S_STATS_LINE_OFFSET.m_x, y + S_STATS_LINE_OFFSET.m_y + S_STATS_LINE_SPACING * (float)(*line), 0, buffer);

	(*line) = (*line) + 1;
}

void g_stats_draw(const ALLEGRO_FONT* font, const g_stats_t* stats, float x, float y)
{
	int32_t line = 0;

	g_stats_draw_line(font, x, y, &line, "Display Size: (%d, %d)", (int32_t)stats->m_display_size.m_x, (int32_t)stats->m_display_size.m_y);
	g_stats_draw_line(font, x, y, &line, "FPS :%.2lf", stats->m_fps);
}

void g_stats_zero_initialize_data(g_stats_t* stats)
{
	if (!stats)
	{
		return;
	}

	stats->m_display_size.m_x = 0.0f;
	stats->m_display_size.m_y = 0.0f;
	stats->m_fps = 0.0;
}
