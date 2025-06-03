#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_bullet.h"

void g_bullet_zero_initialize_data(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_object_zero_initialize_data(&bullet->m_object);
	bullet->m_object.m_max_speed = G_BULLET_MAX_SPEED;
	bullet->m_iterations = 0;
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
	bullet->m_iterations = 0;
}

void g_bullet_reset(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_object_reset(&bullet->m_object);
	bullet->m_iterations = 0;
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

void g_bullet_update_step(g_bullet_t* bullet)
{
	if (!bullet)
	{
		return;
	}

	s_object_update_step(&bullet->m_object);

	if (bullet->m_iterations)
	{
		--bullet->m_iterations;
	}
}
