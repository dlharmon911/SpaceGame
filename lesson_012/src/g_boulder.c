#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "g_constants.h"
#include "g_boulder.h"

void g_boulder_zero_initialize_data(g_boulder_t* boulder)
{
	if (!boulder)
	{
		return;
	}

	s_object_zero_initialize_data(&boulder->m_object);
	boulder->m_object.m_max_speed = G_OBJECT_MAX_SPEED;
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
	if (!boulder)
	{
		return;
	}

	s_object_update(&boulder->m_object);
}
