#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_ship.h"

void g_ship_set_zero(g_ship_t* ship)
{
	if (!ship)
	{
		return;
	}

	s_object_set_zero(&ship->m_object);

	ship->m_object.m_max_speed = G_OBJECT_MAX_SPEED;
}

void g_ship_initialize(const g_texture_data_t* textures, g_ship_t* ship)
{
	if (!textures)
	{
		return;
	}

	if (!ship)
	{
		return;
	}

	g_model_generate_ship_model(&ship->m_ship_model, &ship->m_object.m_model, textures->m_ship_texture);
}

void g_ship_draw(const g_ship_t* ship, int32_t flag)
{
	if (!ship)
	{
		return;
	}

	s_object_draw(&ship->m_object, flag);
}

void g_ship_update(g_ship_t* ship)
{
	s_point_t buffer = { G_GAMESCREEN_SIZE_HALF.m_x, G_GAMESCREEN_SIZE_HALF.m_y };
	const s_point_t* point = NULL;

	if (!ship)
	{
		return;
	}

	s_object_update(&ship->m_object);

	point = &ship->m_object.m_model.m_center;

	if (point->m_x < -buffer.m_x)
	{
		const s_point_t translate = { G_GAMESCREEN_SIZE.m_x, 0.0f };
		s_object_translate(&ship->m_object, &translate);
	}
	else
	{
		if (point->m_x > buffer.m_x)
		{
			const s_point_t translate = { -G_GAMESCREEN_SIZE.m_x, 0.0f };
			s_object_translate(&ship->m_object, &translate);
		}
	}

	if (point->m_y < -buffer.m_y)
	{
		const s_point_t translate = { 0.0f, G_GAMESCREEN_SIZE.m_y };
		s_object_translate(&ship->m_object, &translate);
	}
	else
	{
		if (point->m_y > buffer.m_y)
		{
			const s_point_t translate = { 0.0f, -G_GAMESCREEN_SIZE.m_y };
			s_object_translate(&ship->m_object, &translate);
		}
	}
}

void g_ship_forward_thrust(g_ship_t* ship)
{
	if (!ship)
	{
		return;
	}

	s_object_thrust(&ship->m_object, G_SHIP_THRUST);
}

void g_ship_reverse_thrust(g_ship_t* ship)
{
	if (!ship)
	{
		return;
	}

	s_object_thrust(&ship->m_object, -G_SHIP_THRUST * 0.5f);
}

void g_ship_rotate(g_ship_t* ship, float delta)
{
	if (!ship)
	{
		return;
	}

	s_object_rotate(&ship->m_object, delta);
}
