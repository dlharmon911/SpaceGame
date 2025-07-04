#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_game.h"
#include "g_stats.h"
#include "g_model_data.h"

static g_game_data_t* s_game_data = NULL;

void g_game_set_zero(g_game_data_t* data)
{
	s_game_data = data;

	if (!s_game_data)
	{
		return;
	}
	g_texture_data_set_zero(&s_game_data->m_textures);
	g_stats_set_zero(&s_game_data->m_stats);
	data->m_input_data = NULL;
	data->m_is_running = false;
}

int32_t g_game()
{
	s_log_print("Creating the vertex declaration - ");
	s_vertex_create_decl();
	if (!s_vertex_decl_created())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Creating the game textures\n");
	if (g_texture_data_generate(&s_game_data->m_textures) < 0)
	{
		return -1;
	}

	g_model_generate_ship_model(&s_game_data->m_ship_model, &s_game_data->m_model, s_game_data->m_textures.m_ship_texture);

	return 0;
}

void g_game_destroy_data()
{
	g_texture_data_destroy(&s_game_data->m_textures);

	if (s_vertex_decl_created())
	{
		s_vertex_destroy_decl();
		s_log_println("The vertex declaration has been destroyed");
	}
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
	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);

	al_draw_line(0.0f, -400.0f, 0.0f, 400.0f, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);
	al_draw_line(-400.0f, 0.0f, 400.0f, 0.0f, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);

	s_model_draw(&s_game_data->m_model, S_MODEL_DRAW_FLAG_TEXTURED);

	al_use_transform(&backup);
}
