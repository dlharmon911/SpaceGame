#ifndef _HEADER_GUARD_GAME_H_
#define _HEADER_GUARD_GAME_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "g_constants.h"
#include "g_stats.h"

typedef struct g_game_data_t
{
	g_stats_t m_stats;
	bool m_is_running;
} g_game_data_t;

void g_game_zero_initialize_data(g_game_data_t* data);
void g_game_logic();
void g_game_draw();

#endif // !_HEADER_GUARD_GAME_H_
