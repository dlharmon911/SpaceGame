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

static void g_colllision_reverse_boulders(g_boulder_t* boulder1, g_boulder_t* boulder2, float range, float distance)
{
	s_point_t velocity1 = { 0.0f, 0.0f };
	s_point_t velocity2 = { 0.0f, 0.0f };

	s_point_set(&velocity1, &boulder1->m_object.m_velocity);
	s_point_multiply_f(&velocity1, -1.0f / 10.0f);

	s_point_set(&velocity2, &boulder2->m_object.m_velocity);
	s_point_multiply_f(&velocity2, -1.0f / 10.0f);

	while (distance <= range)
	{
		s_object_translate(&boulder1->m_object, &velocity1);
		s_object_translate(&boulder2->m_object, &velocity2);

		distance = s_point_get_distance_between(&boulder1->m_object.m_model.m_center, &boulder2->m_object.m_model.m_center);
	}
}

static bool g_collision_do_boulder_vs_boulder_collision(g_boulder_t* boulder1, g_boulder_t* boulder2, g_stats_collision_t* stats)
{
	float distance = 0.0f;
	float range = 0.0f;

	if (!boulder1)
	{
		return false;
	}

	if (!boulder2)
	{
		return false;
	}

	if (!stats)
	{
		return false;
	}

	range = boulder1->m_radius + boulder2->m_radius;
	distance = s_point_get_distance_between(&boulder1->m_object.m_model.m_center, &boulder2->m_object.m_model.m_center);

	if (distance <= range)
	{
		++stats->m_collisions_per_frame;

		return true;
	}

	return false;
}

static bool g_collision_do_boulder_vs_boulder_array_collision(g_boulder_array_t* boulder_array, g_boulder_t* boulder1, g_stats_collision_t* stats)
{
	g_boulder_node_t* boulder_node = NULL;
	g_boulder_t* boulder2 = NULL;
	bool collision = false;

	if (!boulder_array)
	{
		return false;
	}

	if (!boulder1)
	{
		return false;
	}

	if (!stats)
	{
		return false;
	}

	for (size_t index = 0; index < boulder_array->m_max_count; ++index)
	{
		boulder_node = &boulder_array->m_boulder[index];

		if (boulder1 != &boulder_node->m_boulder &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder2 = &boulder_node->m_boulder;

			if (g_collision_do_boulder_vs_boulder_collision(boulder1, boulder2, stats))
			{
				collision = true;
			}
		}
	}

	return collision;
}

bool g_collision_do_boulder_array_vs_boulder_array_collision(g_boulder_array_t* boulder_array, g_stats_collision_t* stats)
{
	g_boulder_node_t* boulder_node = NULL;
	g_boulder_t* boulder1 = NULL;
	bool collision = false;

	if (!boulder_array)
	{
		return false;
	}

	if (!stats)
	{
		return false;
	}

	for (size_t index = 0; index < boulder_array->m_max_count; ++index)
	{
		boulder_node = &boulder_array->m_boulder[index];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder1 = &boulder_node->m_boulder;

			if (g_collision_do_boulder_vs_boulder_array_collision(boulder_array, boulder1, stats))
			{
				collision = true;
			}
		}
	}

	return collision;
}
