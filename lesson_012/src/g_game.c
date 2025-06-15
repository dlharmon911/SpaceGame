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
#include "g_bullet.h"
#include "g_bullet_array.h"
#include "g_game.h"

void g_game_zero_initialize_data(g_game_data_t* data)
{
	if (!data)
	{
		return;
	}

	g_texture_zero_initialize_data(&data->m_textures);
	g_stats_zero_initialize_data(&data->m_stats);
	g_ship_zero_initialize_data(&data->m_ship);
	g_star_array_zero_initialize_data(&data->m_star_array);
	g_boulder_array_zero_initialize_data(&data->m_boulder_array);
	data->m_input_data = NULL;
	data->m_settings = NULL;
	data->m_is_running = false;
}

int32_t g_game_initialize_data(g_game_data_t* data)
{
	s_log_print("Creating the vertex declaration - ");
	s_vertex_create_decl();
	if (!s_vertex_decl_created())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	if (G_TEXTURES_GENERATE_NEW)
	{
		s_log_print("Creating the game textures - ");
		if (g_texture_initialize_data(&data->m_textures) < 0)
		{
			s_log_println("failure");
			return -1;
		}
		s_log_println("success");
	}
	else
	{
		s_log_printf("Loading the game textures: \"%s\" - ", G_TEXTURE_ARCHIVE_FILENAME);
		if (g_load_textures(&data->m_textures, G_TEXTURE_ARCHIVE_FILENAME) < 0)
		{
			s_log_println("failure");
			return -1;
		}
		s_log_println("success");
	}

	s_log_print("Creating the boulder array - ");
	if (g_boulder_array_initialize(&data->m_boulder_array, G_BOULDER_INITIAL_COUNT) < 0)
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	g_ship_initialize(data->m_textures.m_texture[G_TEXTURE_SHIP], &data->m_ship);
	data->m_stats.m_ship_position = &data->m_ship.m_object.m_model.m_center;
	g_boulder_array_scatter(data->m_textures.m_texture[G_TEXTURE_BOULDER], &data->m_boulder_array);
	g_star_array_scatter(data->m_textures.m_texture[G_TEXTURE_STAR], &data->m_star_array);

	data->m_stats.m_star_count = data->m_star_array.m_count;
	data->m_stats.m_boulder_count = s_vector_get_size(data->m_boulder_array.m_boulder_list);
	data->m_stats.m_boulder_capacity = s_vector_get_capacity(data->m_boulder_array.m_boulder_list);
	data->m_stats.m_bullet_count = &data->m_ship.m_bullet_array.m_count;
	data->m_stats.m_bullet_capacity = &data->m_ship.m_bullet_array.m_max_count;

	return 0;
}

void g_game_destroy_data(g_game_data_t* data)
{
	g_boulder_array_free(&data->m_boulder_array);
	g_texture_unitialize_data(&data->m_textures);

	if (s_vertex_decl_created())
	{
		s_vertex_destroy_decl();
		s_log_println("The vertex declaration has been destroyed");
	}
}

void g_game_logic(g_game_data_t* data)
{
	if (s_input_was_keyboard_button_released(data->m_input_data, ALLEGRO_KEY_ESCAPE))
	{
		data->m_is_running = false;
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_ESCAPE);
	}

	if (s_input_was_keyboard_button_released(data->m_input_data, ALLEGRO_KEY_F3))
	{
		++data->m_settings->m_game.m_draw_flag;
		if (data->m_settings->m_game.m_draw_flag == S_MODEL_DRAW_FLAG_COUNT)
		{
			data->m_settings->m_game.m_draw_flag = 0;
		}
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_F3);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_UP) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_W))
	{
		g_ship_forward_thrust(&data->m_ship);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_DOWN) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_S))
	{
		g_ship_reverse_thrust(&data->m_ship);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_LEFT) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_A))
	{
		g_ship_rotate(&data->m_ship, G_SHIP_ROTATE_AMOUNT);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_RIGHT) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_D))
	{
		g_ship_rotate(&data->m_ship, -G_SHIP_ROTATE_AMOUNT);
	}

	if (s_input_was_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_SPACE))
	{
		g_ship_fire_bullet(&data->m_ship);
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_SPACE);
	}

	g_ship_update(&data->m_ship);
	g_star_array_update(&data->m_star_array, &data->m_ship.m_object.m_velocity);
	g_boulder_array_update(&data->m_boulder_array);
}

void g_game_draw(const g_game_data_t* data)
{
	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);

	al_draw_line(0.0f, G_GAMESCREEN_TOP_LEFT.m_y, 0.0f, G_GAMESCREEN_BOTTOM_RIGHT.m_y, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);
	al_draw_line(G_GAMESCREEN_TOP_LEFT.m_x, 0.0f, G_GAMESCREEN_BOTTOM_RIGHT.m_x, 0.0f, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);

	g_star_array_draw(&data->m_star_array, data->m_settings->m_game.m_draw_flag);
	g_boulder_array_draw(&data->m_boulder_array, data->m_settings->m_game.m_draw_flag);
	g_ship_draw(&data->m_ship, data->m_settings->m_game.m_draw_flag);

	al_use_transform(&backup);
}
