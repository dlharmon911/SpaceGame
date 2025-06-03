#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "g_constants.h"
#include "g_boulder.h"
#include "g_boulder_array.h"

void g_boulder_array_zero_initialize_data(g_boulder_array_t* boulder_array)
{
	if (!boulder_array)
	{
		return;
	}

	g_boulder_node_t* node = NULL;

	boulder_array->m_count = 0;
	boulder_array->m_max_count = G_BOULDER_MAX_COUNT;

	for (size_t i = 0; i < G_BOULDER_MAX_COUNT; ++i)
	{
		node = &boulder_array->m_boulder[i];

		s_flags_set(&node->m_status, G_BOULDER_STATUS_UNINITIALIZED);
		g_boulder_zero_initialize_data(&node->m_boulder);
	}
}

void g_boulder_array_draw(const g_boulder_array_t* boulder_array, int32_t flag)
{
	const g_boulder_node_t* boulder_node = NULL;
	const g_boulder_t* boulder = NULL;

	if (!boulder_array)
	{
		return;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder = &boulder_node->m_boulder;
			g_boulder_draw(boulder, flag);
		}
	}
}

g_boulder_node_t* g_boulder_array_find_first_dead_boulder(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;

	if (!boulder_array)
	{
		return NULL;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (!s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED))
		{
			return boulder_node;
		}
	}

	return NULL;
}

void g_boulder_array_populate_boulder_data(g_boulder_t* boulder)
{
	float angle = 0.0f;
	float speed = 0.0f;
	s_point_t point = { 0.0f, 0.0f };
	float distance = 0.0f;

	do
	{
		s_point_set_f(&point, 
			s_random_generate_f(G_GAMESCREEN_SIZE.m_x) - G_GAMESCREEN_SIZE_HALF.m_x,
			s_random_generate_f(G_GAMESCREEN_SIZE.m_y) - G_GAMESCREEN_SIZE_HALF.m_y);
		distance = s_point_get_length(&point);

	} while (distance < 100.0f);

	s_model_translate(&boulder->m_object.m_model, &point);

	boulder->m_object.m_rotate_velocity = s_random_generate_constraint_f(G_BOULDER_START_ROTATE_VELOCITY_MIN, G_BOULDER_START_ROTATE_VELOCITY_MAX);
	
	if (s_random_generate(99) < 50)
	{
		boulder->m_object.m_rotate_velocity = -boulder->m_object.m_rotate_velocity;
	}

	angle = s_random_generate_f(S_PI_DOUBLE);
	speed = s_random_generate_constraint_f(G_BOULDER_START_VELOCITY_MIN, G_BOULDER_START_VELOCITY_MAX);
	s_point_set_f(&boulder->m_object.m_velocity, speed * cosf(angle), speed * sinf(angle));
}

void g_boulder_array_scatter(ALLEGRO_BITMAP* texture, g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;

	if (!texture)
	{
		return;
	}

	if (!boulder_array)
	{
		return;
	}

	boulder_array->m_count = G_BOULDER_INITIAL_MAX_COUNT;

	for (size_t i = 0; i < boulder_array->m_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (boulder_node)
		{
			float scale = s_random_generate_constraint_f(G_BOULDER_SCALE_MIN, G_BOULDER_SCALE_MAX);
			g_boulder_initialize(texture, &boulder_node->m_boulder, scale);
			g_boulder_array_populate_boulder_data(&boulder_node->m_boulder);
			s_flags_add(&boulder_node->m_status, G_BOULDER_STATUS_LIVE | G_BOULDER_STATUS_INITIALIZED);
		}
	}
}

void g_boulder_array_update(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;
	g_boulder_t* boulder = NULL;

	if (!boulder_array)
	{
		return;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder = &boulder_node->m_boulder;
			g_boulder_update(boulder);
		}
	}
}

void g_boulder_array_update_step(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;
	g_boulder_t* boulder = NULL;

	if (!boulder_array)
	{
		return;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder = &boulder_node->m_boulder;
			g_boulder_update_step(boulder);
		}
	}
}

static void g_boulder_array_set_boulder(ALLEGRO_BITMAP* texture, g_boulder_t* boulder, const s_point_t* position, const s_point_t* velocity, float scale)
{
	if (!boulder)
	{
		return;
	}

	if (!position)
	{
		return;
	}

	if (!velocity)
	{
		return;
	}

	g_boulder_initialize(texture, boulder, scale);

	s_object_translate(&boulder->m_object, position);
	s_point_set(&boulder->m_object.m_velocity, velocity);

	boulder->m_object.m_rotate_velocity = s_random_generate_constraint_f(G_BOULDER_START_ROTATE_VELOCITY_MIN, G_BOULDER_START_ROTATE_VELOCITY_MAX);
	if (s_random_generate(99) < 50)
	{
		boulder->m_object.m_rotate_velocity = -boulder->m_object.m_rotate_velocity;
	}
}

static void g_boulder_array_split_boulder(g_boulder_array_t* boulder_array, ALLEGRO_BITMAP* texture, const s_point_t* position, const s_point_t* velocity, float scale)
{
	g_boulder_node_t* new_node = NULL;

	s_point_t boulder_velocity = { 0.0f, 0.0f };

	s_point_set(&boulder_velocity, velocity);

	for (size_t i = 0; i < 2; ++i)
	{
		new_node = g_boulder_array_find_first_dead_boulder(boulder_array);

		if (!new_node)
		{
			return;
		}

		g_boulder_reset(&new_node->m_boulder);
		g_boulder_array_set_boulder(texture, &new_node->m_boulder, position, &boulder_velocity, scale);
		s_flags_set(&new_node->m_status, G_BOULDER_STATUS_LIVE | G_BOULDER_STATUS_INITIALIZED);

		s_point_multiply_f(&boulder_velocity, -1.0f);
		++boulder_array->m_count;
	}
}

static void g_boulder_array_process_collision_boulder(g_boulder_array_t* boulder_array, g_boulder_node_t* boulder_node)
{
	s_point_t position = { 0.0f, 0.0f };
	s_point_t velocity = { 0.0f, 0.0f };
	float scale = 0.0f;
	ALLEGRO_BITMAP* texture = NULL;
	float speed = 0.0f;

	if (!boulder_array)
	{
		return;
	}

	if (!boulder_node)
	{
		return;
	}

	speed = s_point_get_length(&velocity);
	if (speed > G_BOULDER_MAX_SPEED)
	{
		s_point_multiply_f(&velocity, G_BOULDER_MAX_SPEED / speed);
	}

	s_point_set(&velocity, &boulder_node->m_boulder.m_object.m_velocity);

	scale = boulder_node->m_boulder.m_scale * G_BOULDER_SHOT_SCALE_MULTIPLIER;
	s_point_set(&position, &boulder_node->m_boulder.m_object.m_model.m_center);
	texture = boulder_node->m_boulder.m_object.m_model.m_texture;
	--boulder_array->m_count;

	s_flags_set(&boulder_node->m_status, G_BOULDER_STATUS_UNINITIALIZED);

	if (scale >= G_BOULDER_SHOT_SCALE_MIN)
	{
		g_boulder_array_split_boulder(boulder_array, texture, &position, &velocity, scale);
	}
}

void g_boulder_array_process_collisions(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;

	if (!boulder_array)
	{
		return;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			!s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			g_boulder_array_process_collision_boulder(boulder_array, boulder_node);
		}
	}
}

void g_boulder_array_apply_window_constraint(g_boulder_array_t* boulder_array, const s_point_t* top_left, const s_point_t* bottom_right)
{
	g_boulder_node_t* boulder_node = NULL;

	if (!boulder_array)
	{
		return;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			g_boulder_apply_window_constraint(&boulder_node->m_boulder, top_left, bottom_right);
		}
	}
}
