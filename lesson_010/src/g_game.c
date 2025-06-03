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
#include "g_game.h"

static g_game_data_t* g_game_data = NULL;

void g_game_zero_initialize_data(g_game_data_t* data)
{
	g_game_data = data;

	if (!g_game_data)
	{
		return;
	}

	g_texture_zero_initialize_data(&g_game_data->m_textures);
	g_stats_zero_initialize_data(&g_game_data->m_stats);
	g_ship_zero_initialize_data(&g_game_data->m_ship);
	g_star_array_zero_initialize_data(&g_game_data->m_star_array);
	g_boulder_array_zero_initialize_data(&data->m_boulder_array);
	g_game_data->m_settings = NULL;
	data->m_is_running = false;
}

int32_t g_game_initialize_data()
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
	if (g_texture_initialize_data(&g_game_data->m_textures) < 0)
	{
		return -1;
	}

	if (g_boulder_array_initialize(&g_game_data->m_boulder_array, G_BOULDER_INITIAL_COUNT) < 0)
	{
		return -1;
	}

	g_ship_initialize(&g_game_data->m_textures, &g_game_data->m_ship);
	g_game_data->m_stats.m_ship_position = &g_game_data->m_ship.m_object.m_model.m_center;
	g_boulder_array_scatter(g_game_data->m_textures.m_boulder, &g_game_data->m_boulder_array);
	g_star_array_scatter(&g_game_data->m_textures, &g_game_data->m_star_array);

	g_game_data->m_stats.m_star_count = g_game_data->m_star_array.m_count;
	g_game_data->m_stats.m_boulder_count = s_vector_get_size(g_game_data->m_boulder_array.m_boulder_list);
	g_game_data->m_stats.m_boulder_capacity = s_vector_get_capacity(g_game_data->m_boulder_array.m_boulder_list);

	return 0;
}

void g_game_destroy_data()
{
	g_boulder_array_free(&g_game_data->m_boulder_array);
	g_texture_unitialize_data(&g_game_data->m_textures);

	if (s_vertex_decl_created())
	{
		s_vertex_destroy_decl();
		s_log_println("The vertex declaration has been destroyed");
	}
}

void g_game_logic()
{
	if (s_input_was_key_button_released(ALLEGRO_KEY_ESCAPE))
	{
		g_game_data->m_is_running = false;
		s_input_acknowledge_key_button(ALLEGRO_KEY_ESCAPE);
	}

	if (s_input_was_key_button_released(ALLEGRO_KEY_F3))
	{
		++g_game_data->m_settings->m_game.m_draw_flag;
		if (g_game_data->m_settings->m_game.m_draw_flag == S_MODEL_DRAW_FLAG_COUNT)
		{
			g_game_data->m_settings->m_game.m_draw_flag = 0;
		}
		s_input_acknowledge_key_button(ALLEGRO_KEY_F3);
	}

	if (s_input_is_key_button_pressed(ALLEGRO_KEY_UP) || s_input_is_key_button_pressed(ALLEGRO_KEY_W))
	{
		g_ship_forward_thrust(&g_game_data->m_ship);
	}

	if (s_input_is_key_button_pressed(ALLEGRO_KEY_DOWN) || s_input_is_key_button_pressed(ALLEGRO_KEY_S))
	{
		g_ship_reverse_thrust(&g_game_data->m_ship);
	}

	if (s_input_is_key_button_pressed(ALLEGRO_KEY_LEFT) || s_input_is_key_button_pressed(ALLEGRO_KEY_A))
	{
		g_ship_rotate(&g_game_data->m_ship, G_SHIP_ROTATE_AMOUNT);
	}

	if (s_input_is_key_button_pressed(ALLEGRO_KEY_RIGHT) || s_input_is_key_button_pressed(ALLEGRO_KEY_D))
	{
		g_ship_rotate(&g_game_data->m_ship, -G_SHIP_ROTATE_AMOUNT);
	}

	g_ship_update(&g_game_data->m_ship);
	g_star_array_update(&g_game_data->m_star_array, &g_game_data->m_ship.m_object.m_velocity);
	g_boulder_array_update(&g_game_data->m_boulder_array);
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

	g_star_array_draw(&g_game_data->m_star_array, g_game_data->m_settings->m_game.m_draw_flag);
	g_boulder_array_draw(&g_game_data->m_boulder_array, g_game_data->m_settings->m_game.m_draw_flag);
	g_ship_draw(&g_game_data->m_ship, g_game_data->m_settings->m_game.m_draw_flag);

	al_use_transform(&backup);
}
