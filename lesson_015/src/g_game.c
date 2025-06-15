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
#include "g_bullet.h"
#include "g_bullet_array.h"
#include "g_collision.h"
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
	s_camera_zero_initialize_data(&data->m_camera);
	s_point_set_zero(&data->m_mouse);
	data->m_input_data = NULL;
	data->m_settings = NULL;
	data->m_apply_constraint = false;
	data->m_is_running = false;
}

int32_t g_game_initialize_data(g_game_data_t* data)
{
	if (!data)
	{
		return -1;
	}

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

	s_log_println("Initializing ship data");
	g_ship_initialize(data->m_textures.m_texture[G_TEXTURE_SHIP], &data->m_ship);
	data->m_stats.m_ship_position = &data->m_ship.m_object.m_model.m_center;
	s_log_println("Initializing and scattering boulders");
	g_boulder_array_scatter(data->m_textures.m_texture[G_TEXTURE_BOULDER], &data->m_boulder_array);
	s_log_println("Initializing and scattering stars");
	g_star_array_scatter(data->m_textures.m_texture[G_TEXTURE_STAR], &data->m_star_array);

	data->m_stats.m_star_count = data->m_star_array.m_count;
	data->m_stats.m_boulder_count = &data->m_boulder_array.m_count;
	data->m_stats.m_boulder_capacity = 0;
	data->m_stats.m_bullet_count = &data->m_ship.m_bullet_array.m_count;
	data->m_stats.m_bullet_capacity = &data->m_ship.m_bullet_array.m_max_count;
	data->m_stats.m_mouse = &data->m_mouse;

	s_camera_set_following(&data->m_camera, &data->m_ship.m_object.m_model.m_center);

	return 0;
}

void g_game_destroy_data(g_game_data_t* data)
{
	if (!data)
	{
		return;
	}

	if (data->m_boulder_array.m_boulder_list)
	{
		g_boulder_array_free(&data->m_boulder_array);
		s_log_println("Releasing boulder array memory");
	}

	s_log_println("Releasing texture memory");
	g_texture_unitialize_data(&data->m_textures);

	if (s_vertex_decl_created())
	{
		s_vertex_destroy_decl();
		s_log_println("The vertex declaration has been destroyed");
	}
}

void g_game_logic(g_game_data_t* data)
{
	if (!data)
	{
		return;
	}

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
		g_ship_thrust(&data->m_ship, G_SHIP_THRUST);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_DOWN) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_S))
	{
		g_ship_thrust(&data->m_ship, G_SHIP_THRUST * -G_SHIP_REVERSE_THRUST_RATIO);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_LEFT) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_A))
	{
		g_ship_rotate(&data->m_ship, G_SHIP_ROTATE_AMOUNT);
	}

	if (s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_RIGHT) || s_input_is_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_D))
	{
		g_ship_rotate(&data->m_ship, -G_SHIP_ROTATE_AMOUNT);
	}

	if (s_input_was_keyboard_button_pressed(data->m_input_data, ALLEGRO_KEY_SPACE) || s_input_was_mouse_button_pressed(data->m_input_data, ALLEGRO_MOUSE_BUTTON_LEFT))
	{
		g_ship_fire_bullet(&data->m_ship);
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_SPACE);
		s_input_acknowledge_mouse_button(data->m_input_data, ALLEGRO_MOUSE_BUTTON_LEFT);
	}

	g_game_update(data);
}

static void g_game_update_step(g_game_data_t* data)
{
	g_ship_update_step(&data->m_ship);
	g_star_array_update_step(&data->m_star_array, &data->m_ship.m_object.m_velocity);
	g_boulder_array_update_step(&data->m_boulder_array);

	if (g_collison_do_boulder_array_vs_bullet_array_collision(&data->m_boulder_array, &data->m_ship.m_bullet_array, &data->m_stats.m_collisions))
	{
		g_boulder_array_process_collisions(&data->m_boulder_array);
		data->m_stats.m_boulder_capacity = s_vector_get_capacity(data->m_boulder_array.m_boulder_list);
	}

	if (data->m_apply_constraint)
	{
		g_ship_apply_window_constraint(&data->m_ship, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);
		g_boulder_array_apply_window_constraint(&data->m_boulder_array, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);
	}
}

void g_game_update(g_game_data_t* data)
{
	if (!data)
	{
		return;
	}

	data->m_stats.m_collisions.m_collisions_per_frame = 0;
	data->m_stats.m_collisions.m_full_collisions_per_frame = 0;

	for (size_t i = 0; i < S_OBJECT_LOGIC_STEP_COUNT; ++i)
	{
		g_game_update_step(data);
	}

	g_star_array_apply_window_constraint(&data->m_star_array, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);

	s_camera_update(&data->m_camera);
}

void g_game_draw(const g_game_data_t* data)
{
	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;

	if (!data)
	{
		return;
	}

	al_clear_to_color(S_COLOR_BLACK.m_al_color);
	g_star_array_draw(&data->m_star_array, data->m_settings->m_game.m_draw_flag);

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);

	if (!data->m_apply_constraint)
	{
		s_camera_translate_transform(&transform, &data->m_camera);
	}
	
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	g_boulder_array_draw(&data->m_boulder_array, data->m_settings->m_game.m_draw_flag);
	g_ship_draw(&data->m_ship, data->m_settings->m_game.m_draw_flag);
	g_bullet_array_draw(&data->m_ship.m_bullet_array, data->m_settings->m_game.m_draw_flag);

	al_use_transform(&backup);

	al_draw_line(0.0f, -G_GAMESCREEN_SIZE_HALF.m_y, 0.0f, G_GAMESCREEN_SIZE_HALF.m_y, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);
	al_draw_line(-G_GAMESCREEN_SIZE_HALF.m_x, 0.0f, G_GAMESCREEN_SIZE_HALF.m_x, 0.0f, al_premul_rgba_f(1.0f, 1.0f, 1.0f, 0.25f), 2.0f);

}
