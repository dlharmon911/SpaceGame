#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_game.h"

static g_game_data_t* s_game_data = NULL;

void g_game_zero_initialize_data(g_game_data_t* data)
{
	data->m_input_data = NULL;
	data->m_is_running = false;
	s_game_data = data;
}

void g_game_logic()
{
	if (s_input_was_keyboard_button_released(s_game_data->m_input_data, ALLEGRO_KEY_ESCAPE))
	{
		s_game_data->m_is_running = false;
		s_input_acknowledge_keyboard_button(s_game_data->m_input_data, ALLEGRO_KEY_ESCAPE);
	}
}

void g_game_draw()
{
	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);
}
