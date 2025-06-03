#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"

bool s_math_is_zero_f(float a)
{
	return s_math_is_equal_f(a, 0.0f);
}

bool s_math_is_equal_f(float a, float b)
{
	return (fabsf(a - b) <= FLT_EPSILON);
}

float s_math_max_f(float a, float b)
{
	if (a > b)
	{
		return a;
	}

	return b;
}

float s_math_min_f(float a, float b)
{
	if (a < b)
	{
		return a;
	}

	return b;
}
