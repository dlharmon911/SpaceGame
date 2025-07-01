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
	boulder->m_scale = 1.0f;
	boulder->m_radius = 0.0f;
}

void g_boulder_reset(g_boulder_t* boulder)
{
	if (!boulder)
	{
		return;
	}

	s_object_reset(&boulder->m_object);
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

	g_model_generate_boulder_model(&boulder->m_boulder_model, &boulder->m_object.m_model, texture, scale, &boulder->m_radius);
	boulder->m_scale = scale;
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
	if (!boulder)
	{
		return;
	}

	s_object_update(&boulder->m_object);
}

void g_boulder_update_step(g_boulder_t* boulder)
{
	if (!boulder)
	{
		return;
	}

	s_object_update_step(&boulder->m_object);
}
