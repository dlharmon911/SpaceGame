#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_triangle.h"

void s_triangle_set_zero(s_triangle_t* triangle)
{
	if (!triangle)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		triangle->m_float_array[i] = 0.0f;
	}
}

void s_triangle_set_p(s_triangle_t* triangle, const s_point_t* point1, const s_point_t* point2, const s_point_t* point3)
{
	if (!triangle)
	{
		return;
	}

	if (!point1)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	if (!point3)
	{
		return;
	}

	const s_triangle_t rhs = { *point1, *point2, *point3 };

	s_triangle_set(triangle, &rhs);
}

void s_triangle_set(s_triangle_t* triangle, const s_triangle_t* triangle2)
{
	if (!triangle)
	{
		return;
	}

	if (!triangle2)
	{
		return;
	}

	for (int32_t i = 0; i < S_TRIANGLE_POINT_COUNT; ++i)
	{
		s_point_set(&triangle->m_point_array[i], &triangle2->m_point_array[i]);
	}
}

void s_triangle_draw(const s_triangle_t* triangle, float x, float y, ALLEGRO_COLOR color, float thickness)
{
	if (!triangle)
	{
		return;
	}

	al_draw_triangle(
		x + triangle->m_point1.m_x, y + triangle->m_point1.m_y,
		x + triangle->m_point2.m_x, y + triangle->m_point2.m_y,
		x + triangle->m_point3.m_x, y + triangle->m_point3.m_y,
		color,
		thickness);
}

void s_triangle_draw_filled(const s_triangle_t* triangle, float x, float y, ALLEGRO_COLOR color)
{
	if (!triangle)
	{
		return;
	}

	al_draw_filled_triangle(
		x + triangle->m_point1.m_x, y + triangle->m_point1.m_y,
		x + triangle->m_point2.m_x, y + triangle->m_point2.m_y,
		x + triangle->m_point3.m_x, y + triangle->m_point3.m_y,
		color);
}
