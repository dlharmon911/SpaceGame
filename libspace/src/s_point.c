#include <allegro5/allegro5.h>
#include <float.h>
#include <math.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"

void s_point_zero_initialize_data(s_point_t* point)
{
	if (!point)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] = 0.0f;
	}
}

void s_point_add_f(s_point_t* point, float x, float y)
{
	if (!point)
	{
		return;
	}

	const s_point_t rhs = { x, y };

	s_point_add(point, &rhs);
}

void s_point_subtract_f(s_point_t* point, float x, float y)
{
	if (!point)
	{
		return;
	}

	const s_point_t rhs = { x, y };

	s_point_subtract(point, &rhs);
}

void s_point_multiply_f(s_point_t* point, float scale)
{
	if (!point)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] *= scale;
	}
}

void s_point_divide_f(s_point_t* point, float scale)
{
	if (s_math_is_zero_f(scale))
	{
		return;
	}

	s_point_multiply_f(point, 1.0f / scale);
}

bool s_point_equals_f(const s_point_t* point, float x, float y)
{
	if (!point)
	{
		return false;
	}

	const s_point_t rhs = { x, y };

	return s_point_equals(point, &rhs);
}

void s_point_set_f(s_point_t* point, float x, float y)
{
	if (!point)
	{
		return;
	}

	const s_point_t rhs = { x, y };

	s_point_set(point, &rhs);
}

void s_point_add(s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] += point2->m_float_array[i];
	}
}

void s_point_subtract(s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] -= point2->m_float_array[i];
	}
}
void s_point_multiply(s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] *= point2->m_float_array[i];
	}
}

void s_point_divide(s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		if (s_math_is_zero_f(point2->m_float_array[i]))
		{
			return;
		}

		point->m_float_array[i] /= point2->m_float_array[i];
	}
}

bool s_point_equals(const s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return false;
	}

	if (!point2)
	{
		return false;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		if (!s_math_is_equal_f(point->m_float_array[i], point2->m_float_array[i]))
		{
			return false;
		}
	}

	return true;
}

void s_point_set(s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] = point2->m_float_array[i];
	}
}

void s_point_set_zero(s_point_t* point)
{
	if (!point)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		point->m_float_array[i] = 0.0f;
	}
}

void s_point_rotate(s_point_t* point, float angle)
{
	if (!point)
	{
		return;
	}

	float x = point->m_x * cosf(angle) - point->m_y * sinf(angle);
	float y = point->m_x * sinf(angle) + point->m_y * cosf(angle);

	s_point_set_f(point, x, y);
}

void s_point_rotate_array(s_point_t* point, size_t count, float angle)
{
	for (size_t i = 0; i < count; ++i)
	{
		s_point_rotate(point + i, angle);
	}
}

void s_point_get_difference(s_point_t* result, const s_point_t* point, const s_point_t* point2)
{
	if (!result)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		result->m_float_array[i] = point->m_float_array[i] - point2->m_float_array[i];
	}
}

float s_point_get_length(const s_point_t* point)
{
	if (!point)
	{
		return NAN;
	}

	float sum = 0.0f;

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		sum += (point->m_float_array[i] * point->m_float_array[i]);
	}

	return sqrtf(sum);
}

float s_point_get_distance_between(const s_point_t* point, const s_point_t* point2)
{
	if (!point)
	{
		return NAN;
	}

	if (!point2)
	{
		return NAN;
	}

	s_point_t difference = { 0.0f, 0.0f };

	s_point_get_difference(&difference, point, point2);

	return s_point_get_length(&difference);
}

float s_point_dot_product(const s_point_t* point, const s_point_t* point2)
{
	float sum = 0.0f;

	if (!point)
	{
		return NAN;
	}

	if (!point2)
	{
		return NAN;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		sum += (point->m_float_array[i] * point2->m_float_array[i]);
	}

	return sum;
}

void s_point_normalize(s_point_t* result, const s_point_t* point)
{
	float length = 0.0f;
	float inverse = 1.0f;

	if (!result)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	length = s_point_get_length(point);

	if (s_math_is_zero_f(length))
	{
		length = 1.0f;
	}

	inverse = 1.0f / length;

	s_point_set(result, point);

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		result->m_float_array[i] *= inverse;
	}
}

static void s_point_make_line(const s_point_t* point, const s_point_t* point2, float* m, float* b)
{
	if (!point)
	{
		return;
	}

	if (!point2)
	{
		return;
	}

	if (!m)
	{
		return;
	}

	if (!b)
	{
		return;
	}

	if (s_math_is_equal_f(point->m_x, point2->m_x))
	{
		return;
	}

	*m = (point2->m_y - point->m_y) / (point2->m_x - point->m_x);
	*b = point->m_y - *m * point->m_x;
}

void s_point_find_point_on_line(s_point_t* result, const s_point_t* point, const s_point_t* line_point1, const s_point_t* line_point2)
{
	if (!result)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	if (!line_point1)
	{
		return;
	}

	if (!line_point2)
	{
		return;
	}

	float m = 0.0f;
	float b = 0.0f;

	s_point_make_line(line_point1, line_point2, &m, &b);

	float m_perp = -1 / m;
	float b_perp = point->m_y - m_perp * point->m_x;

	result->m_x = (b_perp - b) / (m - m_perp);
	result->m_y = m * result->m_x + b;
}

float s_point_line_point_distance(const s_point_t* point, const s_point_t* line_point1, const s_point_t* line_point2)
{
	s_point_t ab = { 0.0f, 0.0f };
	s_point_t be = { 0.0f, 0.0f };
	s_point_t ae = { 0.0f, 0.0f };
	float ab_be = 0.0f;
	float ab_ae = 0.0f;
	s_point_t line_point = { 0.0f, 0.0f };

	if (!point)
	{
		return NAN;
	}

	if (!line_point1)
	{
		return NAN;
	}

	if (!line_point2)
	{
		return NAN;
	}

	s_point_set(&ab, line_point2);
	s_point_subtract(&ab, line_point1);

	s_point_set(&be, point);
	s_point_subtract(&be, line_point2);

	s_point_set(&ae, point);
	s_point_subtract(&ae, line_point1);

	ab_be = s_point_dot_product(&ab, &be);
	ab_ae = s_point_dot_product(&ab, &ae);

	if (ab_be > 0)
	{
		return s_point_get_length(&be);
	}

	if (ab_ae < 0)
	{
		return s_point_get_length(&ae);
	}

	s_point_find_point_on_line(&line_point, point, line_point1, line_point2);

	return s_point_get_distance_between(point, &line_point);
}

void s_point_translate(ALLEGRO_TRANSFORM* transform, const s_point_t* point)
{
	if (!transform)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	al_translate_transform(transform, point->m_x, point->m_y);
}

void s_point_translate_f(ALLEGRO_TRANSFORM* transform, float x, float y)
{
	if (!transform)
	{
		return;
	}

	al_translate_transform(transform, x, y);
}

void s_point_scale(ALLEGRO_TRANSFORM* transform, const s_point_t* point)
{
	if (!transform)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	al_scale_transform(transform, point->m_x, point->m_y);
}
