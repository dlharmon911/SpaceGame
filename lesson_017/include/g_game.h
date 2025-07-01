#ifndef _HEADER_GUARD_GAME_H_
#define _HEADER_GUARD_GAME_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "g_constants.h"
#include "g_stats.h"
#include "g_models.h"
#include "g_textures.h"
#include "g_ship.h"
#include "g_star.h"
#include "g_star_array.h"
#include "g_boulder.h"
#include "g_boulder_array.h"
#include "g_radar.h"
#include "g_settings.h"

/// <summary>Data struct for game</summary>
typedef struct g_game_data_t
{
	/// <summary>Game status information</summary>
	g_stats_t m_stats;

	/// <summary>Container that holds all textures</summary>
	g_texture_list_t m_textures;

	/// <summary>Ship entity data</summary>
	g_ship_t m_ship;

	/// <summary>Star entity data array</summary>
	g_star_array_t m_star_array;

	/// <summary>Boulder entity data array</summary>
	g_boulder_array_t m_boulder_array;

	/// <summary>Input data (keyboard, mouse, joystick)</summary>
	S_INPUT_DATA* m_input_data;

	/// <summary>Configuration settings handler</summary>
	g_settings_t* m_settings;

	/// <summary>Mouse position relative to center</summary>
	s_point_t m_mouse;

	s_viewport_t m_viewport;

	/// <summary>If window constraint turned off, camera follows ship</summary>
	s_camera_t m_camera;

	bool m_fixed_angle;

	/// <summary>Built-in 8x8 font</summary>
	ALLEGRO_FONT* m_builtin_font;

	g_radar_t m_radar;

	bool m_paused;

	/// <summary>Boolean set if object should be constrained to window</summary>
	bool m_apply_constraint;

	/// <summary>Boolean set if game should continue to process</summary>
	bool m_is_running;
} g_game_data_t;

/// <summary>Zero-initializes game data struct</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_set_zero(g_game_data_t* data);

/// <summary>Initializes game object and model data</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>int32_t = 0 on success, -1 on failure</returns>
int32_t g_game_initialize(g_game_data_t* data);

/// <summary>Release game data memory</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_destroy_data(g_game_data_t* data);

/// <summary>Update game logic</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_update(g_game_data_t* data);

/// <summary>Process game logic</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_logic(g_game_data_t* data);

/// <summary>Draw game to display</summary>
/// <param name='data'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_draw(const g_game_data_t* data);

#endif // !_HEADER_GUARD_GAME_H_
