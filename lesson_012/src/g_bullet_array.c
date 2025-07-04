#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include <math.h>
#include "g_constants.h"
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_bullet.h"
#include "g_bullet_array.h"

void g_bullet_array_set_zero(g_bullet_array_t* bullet_array)
{
	if (!bullet_array)
	{
		return;
	}

	g_bullet_node_t* node = NULL;

	bullet_array->m_count = 0;
	bullet_array->m_max_count = G_BULLET_INITIAL_MAX_COUNT;

	for (size_t i = 0; i < G_BULLET_MAX_COUNT; ++i)
	{
		node = &bullet_array->m_bullet[i];

		node->m_status = G_BULLET_STATUS_DEFAULT;
		g_bullet_set_zero(&node->m_bullet);
	}
}

void g_bullet_array_initialize(ALLEGRO_BITMAP* texture, g_bullet_array_t* bullet_array)
{
	if (!texture)
	{
		return;
	}

	if (!bullet_array)
	{
		return;
	}

	g_bullet_node_t* node = NULL;

	for (size_t i = 0; i < G_BULLET_MAX_COUNT; ++i)
	{
		node = &bullet_array->m_bullet[i];

		node->m_status = G_BULLET_STATUS_DEFAULT;
		g_bullet_initialize(texture, &node->m_bullet);
	}

	bullet_array->m_count = 0;
	bullet_array->m_max_count = G_BULLET_INITIAL_MAX_COUNT;
}

g_bullet_node_t* g_bullet_array_activate(g_bullet_array_t* bullet_array)
{
	g_bullet_node_t* node = NULL;

	if (!bullet_array)
	{
		return NULL;
	}

	for (size_t i = 0; i < bullet_array->m_max_count; ++i)
	{
		node = &bullet_array->m_bullet[i];

		if (!(node->m_status & G_BULLET_STATUS_LIVE))
		{
			return node;
		}
	}

	return NULL;
}

void g_bullet_array_draw(const g_bullet_array_t* bullet_array, int32_t flag)
{
	const g_bullet_node_t* node = NULL;

	if (!bullet_array)
	{
		return;
	}

	for (size_t i = 0; i < bullet_array->m_max_count; ++i)
	{
		node = &bullet_array->m_bullet[i];

		if (node->m_status & G_BULLET_STATUS_LIVE)
		{
			g_bullet_draw(&bullet_array->m_bullet[i].m_bullet, flag);
		}
	}
}

static void g_bullet_array_validate(g_bullet_node_t* node)
{
	const s_point_t buffer = { G_GAMESCREEN_SIZE_HALF.m_x, G_GAMESCREEN_SIZE_HALF.m_y };
	const s_point_t* point = NULL;

	if (!node)
	{
		return;
	}

	point = &node->m_bullet.m_object.m_model.m_center;

	if (point->m_x < -buffer.m_x)
	{
		node->m_status ^= G_BULLET_STATUS_LIVE;
	}
	else
	{
		if (point->m_x > buffer.m_x)
		{
			node->m_status ^= G_BULLET_STATUS_LIVE;
		}
	}

	if (point->m_y < -buffer.m_y)
	{
		node->m_status ^= G_BULLET_STATUS_LIVE;
	}
	else
	{
		if (point->m_y > buffer.m_y)
		{
			node->m_status ^= G_BULLET_STATUS_LIVE;
		}
	}
}

void g_bullet_array_update(g_bullet_array_t* bullet_array)
{
	g_bullet_node_t* node = NULL;
	g_bullet_t* bullet = NULL;

	if (!bullet_array)
	{
		return;
	}

	for (size_t i = 0; i < bullet_array->m_max_count; ++i)
	{
		node = &bullet_array->m_bullet[i];

		if (node->m_status & G_BULLET_STATUS_LIVE)
		{
			bullet = &node->m_bullet;

			g_bullet_update(bullet);
			g_bullet_array_validate(node);

			if (!(node->m_status & G_BULLET_STATUS_LIVE))
			{
				node->m_status = G_BULLET_STATUS_DEFAULT;
				g_bullet_reset(bullet);
				--bullet_array->m_count;
			}
		}
	}
}

bool g_bullet_array_fire(g_bullet_array_t* bullet_array, const s_object_t* player)
{
	g_bullet_node_t* node = NULL;
	g_bullet_t* bullet = NULL;

	if (!bullet_array)
	{
		return false;
	}

	if (!player)
	{
		return false;
	}

	node = g_bullet_array_activate(bullet_array);

	if (!node)
	{
		return false;
	}

	node->m_status |= G_BULLET_STATUS_LIVE;
	++bullet_array->m_count;

	bullet = &node->m_bullet;

	float d = G_SHIP_SIZE.m_y * G_SHIP_CENTER_POINT.m_y * G_SHIP_SIZE_SCALE;

	s_object_rotate(&bullet->m_object, player->m_facing);
	bullet->m_object.m_facing = player->m_facing;

	s_point_t pos = { 0.0f, 0.0f };

	s_point_set(&pos, &player->m_model.m_center);
	s_point_add_f(&pos, d * cosf(player->m_facing), d * sinf(player->m_facing));

	s_object_translate(&bullet->m_object, &pos);
	s_point_set_f(&bullet->m_object.m_velocity, G_BULLET_SPEED * cosf(bullet->m_object.m_facing), G_BULLET_SPEED * sinf(bullet->m_object.m_facing));

	return true;
}
