#ifndef _HEADER_GUARD_SETTINGS_H_
#define _HEADER_GUARD_SETTINGS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>

typedef struct g_settings_display_t
{
	s_point_t m_size;
} g_settings_display_t;

typedef struct g_settings_game_t
{
	int32_t m_draw_flag;
} g_settings_game_t;

typedef struct g_settings_t
{
	g_settings_display_t m_display;
	g_settings_game_t m_game;
} g_settings_t;

int32_t g_settings_load(const char* filename, g_settings_t* settings);
int32_t g_settings_save(const char* filename, const g_settings_t* settings);

#endif // !_HEADER_GUARD_SETTINGS_H_
