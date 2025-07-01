#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "g_constants.h"
#include "g_boulder.h"
#include "g_boulder_array.h"

void g_boulder_array_set_zero(g_boulder_array_t* boulder_array)
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

	boulder_array->m_boulder_list = s_vector_create_with_initial_capacity(sizeof(g_boulder_node_t), initial_size);

	if (!boulder_array->m_boulder_list)
	{
		return -1;
	}

	g_boulder_set_zero(&node.m_boulder);
	node.m_status = 0;

	for (size_t i = 0; i < initial_size; ++i)
	{
		s_vector_push_back(boulder_array->m_boulder_list, &node);
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

void g_boulder_array_draw(g_boulder_array_t* boulder_array, int32_t flag)
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
		boulder = &node->m_boulder;
		g_boulder_draw(boulder, flag);
	}
}

void g_boulder_array_scatter(ALLEGRO_BITMAP* texture, g_boulder_array_t* boulder_array)
{
	g_boulder_node_t* node = NULL;
	g_boulder_t* boulder = NULL;
	size_t size = 0;
	s_point_t point = { 0.0f, 0.0f };

	if (!texture)
	{
		return;
	}

	if (!boulder_array)
	{
		return;
	}

	size = s_vector_get_size(boulder_array->m_boulder_list);

	for (size_t i = 0; i < size; ++i)
	{
		float scale = s_random_generate_constraint_f(G_BOULDER_SCALE_MIN, G_BOULDER_SCALE_MAX);
		node = (g_boulder_node_t*)s_vector_get_value(boulder_array->m_boulder_list, i);
		boulder = &node->m_boulder;

		point.m_x = s_random_generate_f(G_GAMESCREEN_SIZE.m_x) - G_GAMESCREEN_SIZE_HALF.m_x;
		point.m_y = s_random_generate_f(G_GAMESCREEN_SIZE.m_y) - G_GAMESCREEN_SIZE_HALF.m_y;
		g_model_generate_boulder_model(&boulder->m_boulder_model, &boulder->m_object.m_model, texture, scale);

		s_model_translate(&boulder->m_object.m_model, &point);

		boulder->m_object.m_rotate_velocity = s_random_generate_constraint_f(G_BOULDER_START_ROTATE_VELOCITY_MIN, G_BOULDER_START_ROTATE_VELOCITY_MAX);
		if (s_random_percent(0.5f))
		{
			boulder->m_object.m_rotate_velocity = -boulder->m_object.m_rotate_velocity;
		}

		float angle = s_random_generate_f(S_PI_DOUBLE);
		float speed = s_random_generate_constraint_f(G_BOULDER_START_VELOCITY_MIN, G_BOULDER_START_VELOCITY_MAX);
		s_point_set_f(&boulder->m_object.m_velocity, speed * cosf(angle), speed * sinf(angle));
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
		boulder = &node->m_boulder;
		g_boulder_update(boulder);
	}
}
