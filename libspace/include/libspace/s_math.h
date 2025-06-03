#ifndef _HEADER_GUARD_LIBSPACE_MATH_H_
#define _HEADER_GUARD_LIBSPACE_MATH_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "libspace/s_base.h"

static const float S_PI = { (float)ALLEGRO_PI };
static const float S_PI_DOUBLE = { (float)ALLEGRO_PI * 2.0f };
static const float S_PI_HALF = { (float)ALLEGRO_PI * 0.5f };

bool s_math_is_zero_f(float a);
bool s_math_is_equal_f(float a, float b);
float s_math_max_f(float a, float b);
float s_math_min_f(float a, float b);

#endif // !_HEADER_GUARD_LIBSPACE_MATH_H_
