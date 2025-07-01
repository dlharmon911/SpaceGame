#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "g_constants.h"
#include "g_bullet.h"

void g_bullet_set_zero(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_object_set_zero(&bullet->m_object);
	bullet->m_object.m_max_speed = G_BULLET_MAX_SPEED;
}

void g_bullet_initialize(ALLEGRO_BITMAP* texture, g_bullet_t* bullet)
{
	if (!texture)
	{
		return;
	}

	if (!bullet)
	{
		return;
	}

	g_model_generate_bullet_model(&bullet->m_bullet_model, &bullet->m_object.m_model, texture, G_BULLET_SIZE_SCALE);
}

void g_bullet_reset(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_model_center_to_origin(&bullet->m_object.m_model);
	s_model_rotate(&bullet->m_object.m_model, -bullet->m_object.m_facing);
	bullet->m_object.m_facing = 0.0f;
}

void g_bullet_draw(const g_bullet_t* bullet, int32_t flag)
{
	if (!bullet)
	{
		return;
	}

	s_object_draw(&bullet->m_object, flag);
}

void g_bullet_update(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_object_update(&bullet->m_object);
}
