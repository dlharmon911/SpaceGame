#ifndef _HEADER_GUARD_STATES_H_
#define _HEADER_GUARD_STATES_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>

enum G_GAME_STATE_DATA
{
	G_STATE_INVALID = -1,
	G_STATE_GAME,
	G_STATE_COUNT
};

typedef struct g_state_data_t
{
	s_state_t m_state[G_STATE_COUNT];
	int32_t m_index;
} g_state_data_t;

/// <summary>Zero initialize state data</summary>
/// <param name='data'> - pointer to container of state data</param>
/// <returns>n/a</returns>
void g_state_data_set_zero(g_state_data_t* data);

#endif // !_HEADER_GUARD_STATES_H_
