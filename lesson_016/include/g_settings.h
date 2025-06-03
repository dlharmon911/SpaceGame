#ifndef _HEADER_GUARD_SETTINGS_H_
#define _HEADER_GUARD_SETTINGS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>

/// <summary>Data struct for display settings</summary>
typedef struct g_settings_display_t
{
	/// <summary>Display size</summary>
	s_point_t m_size;
} g_settings_display_t;

/// <summary>Data struct for game settings</summary>
typedef struct g_settings_game_t
{
	/// <summary>Model draw flag</summary>
	int32_t m_draw_flag;
} g_settings_game_t;

/// <summary>Data struct for settings</summary>
typedef struct g_settings_t
{
	/// <summary>Display settings</summary>
	g_settings_display_t m_display;

	/// <summary>Game settings</summary>
	g_settings_game_t m_game;
} g_settings_t;

/// <summary>Read the settings from file</summary>
/// <param name='filename'> - name of the file</param>
/// <param name='setting'> - settings data pointer</param>
/// <returns>int32_t - 0 on success, -1 on failure</returns>
int32_t g_settings_load(const char* filename, g_settings_t* settings);

/// <summary>Write the settings to file</summary>
/// <param name='filename'> - name of the file</param>
/// <param name='setting'> - settings data pointer</param>
/// <returns>int32_t - 0 on success, -1 on failure</returns>
int32_t g_settings_save(const char* filename, const g_settings_t* settings);

#endif // !_HEADER_GUARD_SETTINGS_H_
