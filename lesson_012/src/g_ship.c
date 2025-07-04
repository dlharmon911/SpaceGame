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
	g_bullet_array_set_zero(&ship->m_bullet_array);

	ship->m_object.m_max_speed = G_OBJECT_MAX_SPEED;
}

void g_ship_initialize(ALLEGRO_BITMAP* texture, g_ship_t* ship)
{
	if (!texture)
	{
		return;
	}

	if (!ship)
	{
		return;
	}

	g_model_generate_ship_model(&ship->m_ship_model, &ship->m_object.m_model, texture);
	g_bullet_array_initialize(texture, &ship->m_bullet_array);
}

void g_ship_draw(const g_ship_t* ship, int32_t flag)
{
	if (!ship)
	{
		return;
	}

	s_object_draw(&ship->m_object, flag);
	g_bullet_array_draw(&ship->m_bullet_array, flag);
}

void g_ship_update(g_ship_t* ship)
{
	if (!ship)
	{
		return;
	}

	g_bullet_array_update(&ship->m_bullet_array);
	s_object_update(&ship->m_object);

	s_model_validate_screen(&ship->m_object.m_model, &G_GAMESCREEN_TOP_LEFT, &G_GAMESCREEN_BOTTOM_RIGHT);
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

	s_object_thrust(&ship->m_object, -G_SHIP_THRUST * G_SHIP_REVERSE_THRUST_RATIO);
}

void g_ship_rotate(g_ship_t* ship, float delta)
{
	if (!ship)
	{
		return;
	}

	s_object_rotate(&ship->m_object, delta);
}

bool g_ship_fire_bullet(g_ship_t* ship)
{
	if (!ship)
	{
		return false;
	}

	return g_bullet_array_fire(&ship->m_bullet_array, &ship->m_object);
}
