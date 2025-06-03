#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_circle.h"

void s_circle_zero_initialize_data(s_circle_t* circle)
{
	if (!circle)
	{
		return;
	}

	s_point_set_zero(&circle->m_center);
	circle->m_radius = 0.0f;
}

void s_circle_set(s_circle_t* circle, const s_circle_t* circle2)
{
	if (!circle)
	{
		return;
	}

	if (!circle2)
	{
		return;
	}

	s_point_set(&circle->m_center, &circle2->m_center);
	circle->m_radius = circle2->m_radius;
}

void s_circle_set_p(s_circle_t* circle, const s_point_t* center, float radius)
{
	if (!circle)
	{
		return;
	}

	s_point_set(&circle->m_center, center);
	circle->m_radius = radius;
}

void s_circle_draw(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color, float thickness)
{
	if (!circle)
	{
		return;
	}

	al_draw_circle(x + circle->m_center.m_x, y + circle->m_center.m_y, circle->m_radius, color, thickness);
}

void s_circle_draw_filled(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color)
{
	if (!circle)
	{
		return;
	}

	al_draw_filled_circle(x + circle->m_center.m_x, y + circle->m_center.m_y, circle->m_radius, color);
}
