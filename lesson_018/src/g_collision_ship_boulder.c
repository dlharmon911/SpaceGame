#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_boulder.h"
#include "g_boulder_array.h"
#include "g_bullet.h"
#include "g_bullet_array.h"
#include "g_collision.h"
#include "g_model_data.h"

static bool g_collisiion_do_boulder_vs_ship_collision(const g_boulder_t* boulder, const g_ship_t* ship, g_stats_collision_t* stats)
{
	if (!boulder)
	{
		return false;
	}

	if (!ship)
	{
		return false;
	}

	const s_index_buffer_t* b_index_buffer = &boulder->m_object.m_model.m_index_buffer;
	const s_vertex_buffer_t* b_vertex_buffer = &boulder->m_object.m_model.m_vertex_buffer;
	s_triangle_t b_triangle = { 0 };
	size_t b_tri_count = b_index_buffer->m_count / S_TRIANGLE_POINT_COUNT;

	const s_index_buffer_t* s_index_buffer = &ship->m_object.m_model.m_index_buffer;
	const s_vertex_buffer_t* s_vertex_buffer = &ship->m_object.m_model.m_vertex_buffer;
	s_triangle_t s_triangle = { 0 };
	size_t stri_count = s_index_buffer->m_count / S_TRIANGLE_POINT_COUNT;

	for (size_t b_index = 0; b_index < b_tri_count; ++b_index)
	{
		for (size_t t = 0; t < S_TRIANGLE_POINT_COUNT; ++t)
		{
			s_point_set(&b_triangle.m_point_array[t], &b_vertex_buffer->m_buffer[b_index_buffer->m_buffer[S_TRIANGLE_POINT_COUNT * b_index + t]].m_point);
		}

		for (size_t s_index = 0; s_index < stri_count; ++s_index)
		{
			for (size_t t = 0; t < S_TRIANGLE_POINT_COUNT; ++t)
			{
				s_point_set(&s_triangle.m_point_array[t], &s_vertex_buffer->m_buffer[s_index_buffer->m_buffer[S_TRIANGLE_POINT_COUNT * s_index + t]].m_point);
			}

			++stats->m_collisions_per_frame;

			if (s_collision_triangle_triangle(&s_triangle, &b_triangle))
			{
				return true;
			}
		}
	}

	return false;
}

bool g_collision_do_boulder_array_vs_ship_collision(const g_boulder_array_t* boulder_array, const g_ship_t* ship, g_stats_collision_t* stats)
{
	const g_boulder_node_t* boulder_node = NULL;
	const g_boulder_t* boulder = NULL;
	float distance = 0.0f;
	const float ship_radius = G_SHIP_SIZE.m_y * G_SHIP_CENTER_POINT.m_y * G_SHIP_SIZE_SCALE;

	if (!boulder_array)
	{
		return false;
	}

	if (!ship)
	{
		return false;
	}

	for (size_t index = 0; index < boulder_array->m_max_count; ++index)
	{
		boulder_node = &boulder_array->m_boulder[index];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder = &boulder_node->m_boulder;

			distance = s_point_get_distance_between(&boulder->m_object.m_model.m_center, &ship->m_object.m_model.m_center);

			if (distance < (boulder->m_radius + ship_radius) &&
				g_collisiion_do_boulder_vs_ship_collision(boulder, ship, stats))
			{
				return true;
			}
		}
	}

	return false;
}
