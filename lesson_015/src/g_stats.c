#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_stats.h"

static const s_point_t G_STATS_LINE_OFFSET = { 0.5f, 0.5f };
static const float G_STATS_LINE_SPACING = 9.0f;
static const ALLEGRO_COLOR G_STATS_COLOR = { 1.0f, 1.0f, 1.0f, 1.0f };

void g_stats_zero_initialize_data(g_stats_t* stats)
{
	if (!stats)
	{
		return;
	}

	stats->m_star_count = 0;
	stats->m_bullet_count = NULL;
	stats->m_bullet_capacity = 0;
	stats->m_boulder_count = NULL;
	stats->m_boulder_capacity = 0;
	stats->m_ship_position = NULL;
	stats->m_mouse = NULL;
	stats->m_collisions.m_collisions_per_frame = 0;
	stats->m_collisions.m_full_collisions_per_frame = 0;
	stats->m_fps = 0.0f;
}

static void g_stats_draw_line(const ALLEGRO_FONT* font, float x, float y, int32_t* line, const char* const format, ...)
{
	static va_list va_arg_list;
	static char buffer[2048];

	buffer[0] = 0;

	va_start(va_arg_list, format);
	vsnprintf(buffer, 2048, format, va_arg_list);
	va_end(va_arg_list);

	al_draw_text(font, G_STATS_COLOR, x + G_STATS_LINE_OFFSET.m_x, y + G_STATS_LINE_OFFSET.m_y + G_STATS_LINE_SPACING * (float)(*line), 0, buffer);

	(*line) = (*line) + 1;
}

static float g_stats_average_fps(const float* farray, size_t size)
{
	float sum = 0.0f;

	if (!farray)
	{
		return 0.0f;
	}

	for (size_t i = 0; i < size; ++i)
	{
		sum += farray[i];
	}

	return sum / (float)size;
}

static bool g_stats_is_initialized(const g_stats_t* stats)
{
	if (!stats)
	{
		return false;
	}

	if (!stats->m_ship_position)
	{
		return false;
	}

	if (!stats->m_settings)
	{
		return false;
	}

	if (!stats->m_boulder_count)
	{
		return false;
	}

	if (!stats->m_boulder_capacity)
	{
		return false;
	}

	if (!stats->m_bullet_count)
	{
		return false;
	}

	if (!stats->m_bullet_capacity)
	{
		return false;
	}

	if (!stats->m_mouse)
	{
		return false;
	}

	return true;
}

void g_stats_draw(const ALLEGRO_FONT* font, const g_stats_t* stats, float x, float y)
{
	static float farray[200];
	static int32_t index = 0;

	int32_t line = 0;

	farray[index] = stats->m_fps;
	++index;
	if (index == 200)
	{
		index = 0;
	}

	if (!font)
	{
		return;
	}

	if (!g_stats_is_initialized(stats))
	{
		return;
	}

	g_stats_draw_line(font, x, y, &line, "Display Size: (%d, %d)", (int32_t)stats->m_settings->m_display.m_size.m_x, (int32_t)stats->m_settings->m_display.m_size.m_y);
	g_stats_draw_line(font, x, y, &line, "Average FPS :%.2f", g_stats_average_fps(farray, 200));
	g_stats_draw_line(font, x, y, &line, "Ship Position : (%d, %d)", (int32_t)stats->m_ship_position->m_x, (int32_t)stats->m_ship_position->m_y);
	g_stats_draw_line(font, x, y, &line, "Mouse Position : (%d, %d)", (int32_t)stats->m_mouse->m_x, (int32_t)stats->m_mouse->m_y);
	g_stats_draw_line(font, x, y, &line, "Star Count : %d", stats->m_star_count);
	g_stats_draw_line(font, x, y, &line, "Boulder Count : %d (%d)", *stats->m_boulder_count, stats->m_boulder_capacity);
	g_stats_draw_line(font, x, y, &line, "Bullet Count : %d (%d)", *stats->m_bullet_count, *stats->m_bullet_capacity);
	g_stats_draw_line(font, x, y, &line, "Bullet/Boulder Collision Checks : %zu (%zu)", stats->m_collisions.m_full_collisions_per_frame, stats->m_collisions.m_collisions_per_frame);
}
