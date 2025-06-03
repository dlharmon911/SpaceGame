#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_boulder.h"
#include "g_boulder_array.h"
#include "g_bullet.h"
#include "g_bullet_array.h"
#include "g_collision.h"
#include "g_models.h"

static bool g_collision_do_boulder_vs_bullet_collision(const g_boulder_t* boulder, const g_bullet_t* bullet, g_stats_collision_t* stats)
{
	s_point_t* point[S_TRIANGLE_POINT_COUNT] = { NULL, NULL, NULL };
	float distance = 0.0f;

	if (!boulder)
	{
		return false;
	}

	if (!bullet)
	{
		return false;
	}

	++stats->m_collisions_per_frame;

	distance = s_point_get_distance_between(&boulder->m_object.m_model.m_center, &bullet->m_object.m_model.m_center);

	if (distance > boulder->m_radius)
	{
		return false;
	}

	for (size_t i = 0; i < boulder->m_object.m_model.m_index_buffer.m_count; i += S_TRIANGLE_POINT_COUNT)
	{
		++stats->m_full_collisions_per_frame;

		for (size_t t = 0; t < S_TRIANGLE_POINT_COUNT; ++t)
		{
			int32_t index = boulder->m_object.m_model.m_index_buffer.m_buffer[i + t];
			s_vertex_t* vertex = &boulder->m_object.m_model.m_vertex_buffer.m_buffer[index];

			point[t] = &vertex->m_point;
		}

		if (s_collision_point_triangle_p(&bullet->m_object.m_model.m_center, point[0], point[1], point[2]))
		{
			return true;
		}
	}

	return false;
}

static bool g_collision_do_boulder_array_vs_bullet_collision(g_boulder_array_t* boulder_array, const g_bullet_t* bullet, g_stats_collision_t* stats)
{
	g_boulder_node_t* boulder_node = NULL;

	if (!boulder_array)
	{
		return false;
	}

	if (!bullet)
	{
		return false;
	}

	for (size_t i = 0; i < boulder_array->m_max_count; ++i)
	{
		boulder_node = &boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE) &&
			g_collision_do_boulder_vs_bullet_collision(&boulder_node->m_boulder, bullet, stats))
		{
			s_flags_toggle(&boulder_node->m_status, G_BOULDER_STATUS_LIVE);

			s_point_t velocity =
			{
				velocity.m_x = bullet->m_object.m_velocity.m_y,
				velocity.m_y = -bullet->m_object.m_velocity.m_x
			};
			float bullet_magnitude = s_point_get_length(&bullet->m_object.m_velocity);
			float boulder_magnitude = s_point_get_length(&bullet->m_object.m_velocity) * 1.75f;
			s_point_multiply_f(&velocity, boulder_magnitude / bullet_magnitude);
			s_point_set(&boulder_node->m_boulder.m_object.m_velocity, &velocity);

			return true;
		}
	}

	return false;
}

bool g_collision_do_boulder_array_vs_bullet_array_collision(g_boulder_array_t* boulder_array, g_bullet_array_t* bullet_array, g_stats_collision_t* stats)
{
	g_bullet_node_t* bullet_node = NULL;
	int32_t hit_count = 0;

	if (!boulder_array)
	{
		return false;
	}

	if (!bullet_array)
	{
		return false;
	}

	for (size_t index = 0; index < bullet_array->m_max_count; ++index)
	{
		bullet_node = &bullet_array->m_bullet[index];

		if (s_flags_is_set(bullet_node->m_status, G_BULLET_STATUS_LIVE) &&
			g_collision_do_boulder_array_vs_bullet_collision(boulder_array, &bullet_node->m_bullet, stats))
		{
			s_flags_toggle(&bullet_node->m_status, G_BULLET_STATUS_LIVE);
			g_bullet_reset(&bullet_node->m_bullet);
			--bullet_array->m_count;

			++hit_count;

			continue;
		}
	}

	return (bool)hit_count;
}
