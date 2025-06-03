#include <allegro5/allegro5.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"
#include "libspace/s_triangle.h"
#include "libspace/s_circle.h"
#include "libspace/s_collision.h"

float s_triangle_calculate_sign(const s_point_t* point1, const s_point_t* point2, const s_point_t* point3);

bool s_collision_point_circle(const s_point_t* point, const s_circle_t* circle)
{
	if (!point)
	{
		return false;
	}

	if (!circle)
	{
		return false;
	}

	float distance = s_point_get_distance_between(point, &circle->m_center);

	return distance <= circle->m_radius;
}

bool s_collision_point_circle_p(const s_point_t* point, const s_point_t* center, float radius)
{
	if (!point)
	{
		return false;
	}

	if (!center)
	{
		return false;
	}

	float distance = s_point_get_distance_between(point, center);

	return distance <= radius;
}

bool s_collision_point_triangle(const s_point_t* point, const s_triangle_t* triangle)
{
	if (!point)
	{
		return false;
	}

	if (!triangle)
	{
		return false;
	}

	float d1 = s_triangle_calculate_sign(point, &triangle->m_point1, &triangle->m_point2);
	float d2 = s_triangle_calculate_sign(point, &triangle->m_point2, &triangle->m_point3);
	float d3 = s_triangle_calculate_sign(point, &triangle->m_point3, &triangle->m_point1);
	bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

bool s_collision_point_triangle_p(const s_point_t* point, const s_point_t* tpoint1, const s_point_t* tpoint2, const s_point_t* tpoint3)
{
	if (!point)
	{
		return false;
	}

	if (!tpoint1)
	{
		return false;
	}

	if (!tpoint2)
	{
		return false;
	}

	if (!tpoint3)
	{
		return false;
	}

	float d1 = s_triangle_calculate_sign(point, tpoint1, tpoint2);
	float d2 = s_triangle_calculate_sign(point, tpoint2, tpoint3);
	float d3 = s_triangle_calculate_sign(point, tpoint3, tpoint1);

	bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

static float s_triangle_calculate_sign(const s_point_t* point1, const s_point_t* point2, const s_point_t* point3)
{
	if (!point1)
	{
		return false;
	}

	if (!point2)
	{
		return false;
	}

	if (!point3)
	{
		return false;
	}

	return (point1->m_x - point3->m_x) * (point2->m_y - point3->m_y) - (point2->m_x - point3->m_x) * (point1->m_y - point3->m_y);
}

static float s_triangle_calculate_determinant(const s_triangle_t* triangle)
{
	if (!triangle)
	{
		return 0.0f;
	}

	return +triangle->m_point1.m_x * (triangle->m_point2.m_y - triangle->m_point3.m_y)
		+ triangle->m_point2.m_x * (triangle->m_point3.m_y - triangle->m_point1.m_y)
		+ triangle->m_point3.m_x * (triangle->m_point1.m_y - triangle->m_point2.m_y);
}

static bool s_triangle_check_winding(const s_triangle_t* triangle, bool allowReversed)
{
	if (!triangle)
	{
		return false;
	}

	float determinant = s_triangle_calculate_determinant(triangle);

	if (determinant < 0.0)
	{
		if (allowReversed)
		{
			s_triangle_t tReverse =
			{
				triangle->m_point3,
				triangle->m_point2,
				triangle->m_point1
			};

			return s_triangle_check_winding(&tReverse, false);
		}

		return false;
	}

	return true;
}

static bool s_triangle_check_boundary_collide(const s_triangle_t* triangle, double eps)
{
	if (!triangle)
	{
		return false;
	}

	return s_triangle_calculate_determinant(triangle) < eps;
}

static bool s_triangle_check_boundary_collide_p(const s_point_t* point1, const s_point_t* point2, const s_point_t* point3, double eps)
{
	if (!point1)
	{
		return false;
	}

	if (!point2)
	{
		return false;
	}

	if (!point3)
	{
		return false;
	}

	s_triangle_t triangle = { {{*point1, *point2, *point3}} };
	return s_triangle_check_boundary_collide(&triangle, eps);
}

static bool s_triangle_check_boundary_doesnot_collide(const s_triangle_t* triangle, double eps)
{
	if (!triangle)
	{
		return false;
	}

	return s_triangle_calculate_determinant(triangle) <= eps;
}

static bool s_triangle_check_boundary_doesnot_collide_p(const s_point_t* point1, const s_point_t* point2, const s_point_t* point3, double eps)
{
	if (!point1)
	{
		return false;
	}

	if (!point2)
	{
		return false;
	}

	if (!point3)
	{
		return false;
	}

	s_triangle_t triangle = { {{*point1, *point2, *point3}} };
	return s_triangle_check_boundary_doesnot_collide(&triangle, eps);
}

static bool s_collision_triangle_triangle_with_settings(const s_triangle_t* triangle1,
	const s_triangle_t* triangle2,
	double eps, bool allowReversed, bool onBoundary)
{
	//Triangles must be expressed anti-clockwise
	ALLEGRO_ASSERT(s_triangle_check_winding(triangle1, allowReversed));
	ALLEGRO_ASSERT(s_triangle_check_winding(triangle2, allowReversed));

	//For edge E of triangle 1,
	for (int i = 0; i < 3; i++)
	{
		int j = (i + 1) % 3;

		if (onBoundary)
		{
			//Check all points of triangle 2 lay on the external side of the edge E. If
			//they do, the triangles do not collide.
			if (s_triangle_check_boundary_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[0], eps) &&
				s_triangle_check_boundary_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[1], eps) &&
				s_triangle_check_boundary_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[2], eps))
			{
				return false;
			}
		}
		else
		{
			if (s_triangle_check_boundary_doesnot_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[0], eps) &&
				s_triangle_check_boundary_doesnot_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[1], eps) &&
				s_triangle_check_boundary_doesnot_collide_p(&triangle1->m_point_array[i], &triangle1->m_point_array[j], &triangle2->m_point_array[2], eps))
			{
				return false;
			}
		}

		if (onBoundary)
		{
			//Check all points of triangle 2 lay on the external side of the edge E. If
			//they do, the triangles do not collide.
			if (s_triangle_check_boundary_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[0], eps) &&
				s_triangle_check_boundary_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[1], eps) &&
				s_triangle_check_boundary_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[2], eps))
			{
				return false;
			}
		}
		else
		{
			if (s_triangle_check_boundary_doesnot_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[0], eps) &&
				s_triangle_check_boundary_doesnot_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[1], eps) &&
				s_triangle_check_boundary_doesnot_collide_p(&triangle2->m_point_array[i], &triangle2->m_point_array[j], &triangle1->m_point_array[2], eps))
			{
				return false;
			}
		}
	}
	//The triangles collide
	return true;
}

bool s_collision_triangle_triangle(const s_triangle_t* triangle, const s_triangle_t* triangle2)
{
	return s_collision_triangle_triangle_with_settings(triangle, triangle2, FLT_EPSILON, false, true);
}

bool s_collision_triangle_circle(const s_triangle_t* triangle, const s_circle_t* circle)
{
	if (!triangle)
	{
		return false;
	}

	if (!circle)
	{
		return false;
	}

	float distance[S_TRIANGLE_POINT_COUNT] = { 0.0f, 0.0f, 0.0f };

	for (int32_t i = 0; i < S_TRIANGLE_POINT_COUNT; ++i)
	{
		distance[i] = s_point_get_distance_between(&triangle->m_point_array[i], &circle->m_center);

		if (distance[i] <= circle->m_radius)
		{
			return true;
		}
	}

	float line_distance = s_point_line_point_distance(&circle->m_center, &triangle->m_point1, &triangle->m_point2);

	if (line_distance < circle->m_radius)
	{
		return true;
	}

	return false;
}
