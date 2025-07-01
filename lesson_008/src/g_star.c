#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"
#include "g_star.h"

void g_star_set_zero(g_star_t* star)
{
	if (!star)
	{
		return;
	}

	s_object_set_zero(&star->m_object);
	star->m_z = 0.0f;
}

void g_star_initialize(const g_texture_list_t* texture_list, g_star_t* star, float z)
{
	if (!texture_list)
	{
		return;
	}

	if (!star)
	{
		return;
	}

	g_model_generate_star_model(&star->m_star_model, &star->m_object.m_model, texture_list->m_star, z);
	star->m_z = z;
}

void g_star_draw(const g_star_t* star, int32_t flag)
{
	if (!star)
	{
		return;
	}

	s_object_draw(&star->m_object, flag);
}

void g_star_update(g_star_t* star, const s_point_t* velocity)
{
	s_point_t buffer = { G_GAMESCREEN_SIZE_HALF.m_x, G_GAMESCREEN_SIZE_HALF.m_y };
	s_point_t delta = { 0.0f, 0.0f };
	s_point_t point = { 0.0f, 0.0f };

	if (!star)
	{
		return;
	}

	if (!velocity)
	{
		return;
	}

	s_point_set(&point, &star->m_object.m_model.m_center);
	s_point_add(&delta, velocity);
	s_point_add(&point, velocity);

	if (point.m_x < -buffer.m_x)
	{
		delta.m_x = G_GAMESCREEN_SIZE.m_x;
	}
	else
	{
		if (point.m_x > buffer.m_x)
		{
			delta.m_x = -G_GAMESCREEN_SIZE.m_x;
		}
	}

	if (point.m_y < -buffer.m_y)
	{
		delta.m_y = G_GAMESCREEN_SIZE.m_y;
	}
	else
	{
		if (point.m_y > buffer.m_y)
		{
			delta.m_y = -G_GAMESCREEN_SIZE.m_y;
		}
	}

	s_object_translate(&star->m_object, &delta);
}
