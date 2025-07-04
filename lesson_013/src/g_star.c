#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_star.h"

void g_star_set_zero(g_star_t* star)
{
	if (!star)
	{
		return;
	}

	s_object_set_zero(&star->m_object);
	star->m_object.m_max_speed = G_OBJECT_MAX_SPEED;
	star->m_z = 0.0f;
}

void g_star_initialize(ALLEGRO_BITMAP* texture, g_star_t* star, float scale)
{
	if (!texture)
	{
		return;
	}

	if (!star)
	{
		return;
	}

	g_model_generate_star_model(&star->m_star_model, &star->m_object.m_model, texture, scale);
	star->m_z = scale;
}

void g_star_draw(const g_star_t* star, int32_t flag)
{
	if (!star)
	{
		return;
	}

	s_object_draw(&star->m_object, flag);
}

void g_star_update(g_star_t* star)
{
	if (!star)
	{
		return;
	}

	s_object_update(&star->m_object);
}

void g_star_update_step(g_star_t* star)
{
	if (!star)
	{
		return;
	}

	s_object_update_step(&star->m_object);
}
