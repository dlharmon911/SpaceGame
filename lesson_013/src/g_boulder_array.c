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

	boulder_array->m_boulder_list = NULL;
}

int32_t g_boulder_array_initialize(g_boulder_array_t* boulder_array, size_t initial_size)
{
	g_boulder_node_t node = { 0 };

	if (!boulder_array)
	{
		return -1;
	}

	boulder_array->m_count = 0;
	boulder_array->m_boulder_list = s_vector_create_with_initial_capacity(sizeof(g_boulder_node_t), initial_size);

	if (!boulder_array->m_boulder_list)
	{
		return -1;
	}

	g_boulder_zero_initialize_data(&node.m_boulder);
	node.m_status = G_BOULDER_STATUS_DEFAULT;

	for (size_t i = 0; i < initial_size; ++i)
	{
		s_vector_push_back(boulder_array->m_boulder_list, &node);
		++boulder_array->m_count;
	}

	return 0;
}

void g_boulder_array_free(g_boulder_array_t* boulder_array)
{
	if (!boulder_array)
	{
		return;
	}

	if (boulder_array->m_boulder_list)
	{
		s_vector_destroy(boulder_array->m_boulder_list);
		boulder_array->m_boulder_list = NULL;
	}
}

size_t g_boulder_array_get_size(const g_boulder_array_t* boulder_array)
{
	if (!boulder_array)
	{
		return 0;
	}

	return s_vector_get_size(boulder_array->m_boulder_list);
}

void g_boulder_array_draw(const g_boulder_array_t* boulder_array, int32_t flag)
{
	const g_boulder_node_t* node = NULL;
	const g_boulder_t* boulder = NULL;
	size_t size = 0;

	if (!boulder_array)
	{
		return;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t i = 0; i < size; ++i)
	{
		node = (g_boulder_node_t*)s_vector_get_value(boulder_array->m_boulder_list, i);

		if (node->m_status & G_BOULDER_STATUS_LIVE)
		{
			boulder = &node->m_boulder;
			g_boulder_draw(boulder, flag);
		}
	}
}

g_boulder_node_t* g_boulder_array_find_first_dead_boulder(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* node = NULL;
	g_boulder_node_t new_node = { 0 };
	size_t size = 0;

	if (!boulder_array)
	{
		return NULL;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t i = 0; i < size; ++i)
	{
		node = s_vector_get_value(boulder_array->m_boulder_list, i);
		if (!(node->m_status & G_BOULDER_STATUS_LIVE))
		{
			return node;
		}
	}

	g_boulder_zero_initialize_data(&new_node.m_boulder);
	new_node.m_status = G_BOULDER_STATUS_DEFAULT;

	s_vector_push_back(boulder_array->m_boulder_list, &new_node);

	return s_vector_get_value(boulder_array->m_boulder_list, size);
}

void g_boulder_array_populate_boulder_data(g_boulder_t* boulder)
{
	float angle = 0.0f;
	float speed = 0.0f;
	s_point_t point =
	{
		s_random_generate_f(G_GAMESCREEN_SIZE.m_x) - G_GAMESCREEN_SIZE_HALF.m_x,
		s_random_generate_f(G_GAMESCREEN_SIZE.m_y) - G_GAMESCREEN_SIZE_HALF.m_y
	};

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
	g_boulder_node_t* node = NULL;

	if (!texture)
	{
		return;
	}

	if (!boulder_array)
	{
		return;
	}

	s_vector_clear(boulder_array->m_boulder_list);

	for (size_t i = 0; i < G_BOULDER_INITIAL_COUNT; ++i)
	{
		node = g_boulder_array_find_first_dead_boulder(boulder_array);

		if (node)
		{
			float scale = s_random_generate_constraint_f(G_BOULDER_SCALE_MIN, G_BOULDER_SCALE_MAX);
			g_boulder_initialize(texture, &node->m_boulder, scale);
			g_boulder_array_populate_boulder_data(&node->m_boulder);
			node->m_status = G_BOULDER_STATUS_DEFAULT;
		}
	}
}

void g_boulder_array_update(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* node = NULL;
	g_boulder_t* boulder = NULL;
	size_t size = 0;

	if (!boulder_array)
	{
		return;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t i = 0; i < size; ++i)
	{
		node = (g_boulder_node_t*)s_vector_get_value(boulder_array->m_boulder_list, i);

		if (node->m_status & G_BOULDER_STATUS_LIVE)
		{
			boulder = &node->m_boulder;
			g_boulder_update(boulder);
			s_model_validate_screen(&boulder->m_object.m_model, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);
		}
	}
}

void g_boulder_array_update_step(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* node = NULL;
	g_boulder_t* boulder = NULL;
	size_t size = 0;

	if (!boulder_array)
	{
		return;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t i = 0; i < size; ++i)
	{
		node = (g_boulder_node_t*)s_vector_get_value(boulder_array->m_boulder_list, i);

		if (node->m_status & G_BOULDER_STATUS_LIVE)
		{
			boulder = &node->m_boulder;
			g_boulder_update_step(boulder);
			s_model_validate_screen(&boulder->m_object.m_model, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);
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

static void g_boulder_array_process_collision_boulder(g_boulder_array_t* boulder_array, g_boulder_node_t* boulder_node)
{
	s_point_t position = { 0.0f, 0.0f };
	s_point_t velocity = { 0.0f, 0.0f };
	float scale = 0.0f;
	ALLEGRO_BITMAP* texture = NULL;
	g_boulder_node_t* new_node = NULL;

	if (!boulder_array)
	{
		return;
	}

	if (!boulder_node)
	{
		return;
	}

	s_point_set(&velocity, &boulder_node->m_boulder.m_object.m_velocity);

	scale = boulder_node->m_boulder.m_scale * G_BOULDER_SHOT_SCALE_MULTIPLIER;
	s_point_set(&position, &boulder_node->m_boulder.m_object.m_model.m_center);
	texture = boulder_node->m_boulder.m_object.m_model.m_texture;

	g_boulder_reset(&boulder_node->m_boulder);
	s_flags_remove(&boulder_node->m_status, G_BOULDER_STATUS_LIVE);

	if (scale > G_BOULDER_SHOT_SCALE_MIN)
	{
		for (size_t i = 0; i < 2; ++i)
		{
			new_node = g_boulder_array_find_first_dead_boulder(boulder_array);

			g_boulder_array_set_boulder(texture, &new_node->m_boulder, &position, &velocity, scale);
			s_point_multiply_f(&velocity, -1.0f);
			s_flags_add(&new_node->m_status, G_BOULDER_STATUS_LIVE);
		}
	}
}

void g_boulder_array_process_collisions(g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* boulder_node = NULL;
	size_t size = 0;

	if (!boulder_array)
	{
		return;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t b = 0; b < size; ++b)
	{
		boulder_node = s_vector_get_value(boulder_array->m_boulder_list, b);

		if (!(boulder_node->m_status & G_BOULDER_STATUS_LIVE))
		{
			g_boulder_array_process_collision_boulder(boulder_array, boulder_node);
		}
	}
	boulder_array->m_count = s_vector_get_size(boulder_array->m_boulder_list);
}
