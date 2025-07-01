#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "g_constants.h"
#include "g_boulder.h"

void g_boulder_set_zero(g_boulder_t* boulder)
{
	if (!boulder)
	{
		return;
	}

	s_object_set_zero(&boulder->m_object);
	boulder->m_object.m_max_speed = G_OBJECT_MAX_SPEED;
	boulder->m_rotate_velocity = 0.0f;
}

void g_boulder_initialize(ALLEGRO_BITMAP* texture, g_boulder_t* boulder, float scale)
{
	if (!texture)
	{
		return;
	}

	if (!boulder)
	{
		return;
	}

	g_model_generate_boulder_model(&boulder->m_boulder_model, &boulder->m_object.m_model, texture, scale);
}

void g_boulder_draw(const g_boulder_t* boulder, int32_t flag)
{
	if (!boulder)
	{
		return;
	}

	s_object_draw(&boulder->m_object, flag);
}

void g_boulder_update(g_boulder_t* boulder)
{
	s_point_t buffer = { G_GAMESCREEN_SIZE_HALF.m_x, G_GAMESCREEN_SIZE_HALF.m_y };
	const s_point_t* point = NULL;

	if (!boulder)
	{
		return;
	}

	s_object_update(&boulder->m_object);

	boulder->m_object.m_facing += boulder->m_rotate_velocity;
	if (boulder->m_object.m_facing < 0.0f)
	{
		boulder->m_object.m_facing += S_PI_DOUBLE;
	}
	if (boulder->m_object.m_facing >= S_PI_DOUBLE)
	{
		boulder->m_object.m_facing -= S_PI_DOUBLE;
	}

	s_object_rotate(&boulder->m_object, boulder->m_rotate_velocity);

	point = &boulder->m_object.m_model.m_center;

	if (point->m_x < -buffer.m_x)
	{
		const s_point_t translate = { G_GAMESCREEN_SIZE.m_x, 0.0f };
		s_object_translate(&boulder->m_object, &translate);
	}
	else
	{
		if (point->m_x > buffer.m_x)
		{
			const s_point_t translate = { -G_GAMESCREEN_SIZE.m_x, 0.0f };
			s_object_translate(&boulder->m_object, &translate);
		}
	}

	if (point->m_y < -buffer.m_y)
	{
		const s_point_t translate = { 0.0f, G_GAMESCREEN_SIZE.m_y };
		s_object_translate(&boulder->m_object, &translate);
	}
	else
	{
		if (point->m_y > buffer.m_y)
		{
			const s_point_t translate = { 0.0f, -G_GAMESCREEN_SIZE.m_y };
			s_object_translate(&boulder->m_object, &translate);
		}
	}
}
