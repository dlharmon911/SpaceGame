#ifndef _HEADER_GUARD_GAME_H_
#define _HEADER_GUARD_GAME_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_stats.h"
#include "g_models.h"
#include "g_textures.h"
#include "g_ship.h"
#include "g_star.h"
#include "g_star_array.h"
#include "g_boulder.h"
#include "g_boulder_array.h"
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

	/// <summary>Configuration settings handler</summary>
	g_settings_t* m_settings;

	/// <summary>Input data (keyboard, mouse, joystick)</summary>
	S_INPUT_DATA* m_input_data;

	/// <summary>Boolean set if game should continue to process</summary>
	bool m_is_running;
} g_game_data_t;

/// <summary>Zero-initializes game data struct</summary>
/// <param name='bullet'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_set_zero(g_game_data_t* data);

/// <summary>Initializes game object and model data</summary>
/// <param name='bullet'> - pointer to container of game data</param>
/// <returns>int32_t = 0 on success, -1 on failure</returns>
int32_t g_game(g_game_data_t* data);

/// <summary>Release game data memory</summary>
/// <param name='bullet'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_destroy_data(g_game_data_t* data);

/// <summary>Process game logic</summary>
/// <param name='bullet'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_logic(g_game_data_t* data);

/// <summary>Draw game to display</summary>
/// <param name='bullet'> - pointer to container of game data</param>
/// <returns>n/a</returns>
void g_game_draw(const g_game_data_t* data);

#endif // !_HEADER_GUARD_GAME_H_
