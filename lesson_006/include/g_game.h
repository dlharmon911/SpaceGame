#ifndef _HEADER_GUARD_GAME_H_
#define _HEADER_GUARD_GAME_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "g_constants.h"
#include "g_stats.h"
#include "g_model_data.h"
#include "g_texture_data.h"

typedef struct g_game_data_t
{
	g_stats_t m_stats;
	g_texture_data_t m_textures;
	g_ship_model_t m_ship_model;
	s_model_t m_model;
	S_INPUT_DATA* m_input_data;
	bool m_is_running;
} g_game_data_t;

void g_game_set_zero(g_game_data_t* data);
int32_t g_game();
void g_game_destroy_data();
void g_game_logic();
void g_game_draw();

#endif // !_HEADER_GUARD_GAME_H_
