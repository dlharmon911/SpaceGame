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
static const float S_PI_THREE_HALF = { (float)ALLEGRO_PI * 1.5f };
static const float S_PI_DEG = { 180.0f };
static const float S_PI_DEG_DOUBLE = { 360.0f };
static const float S_PI_DEG_THREE_HALF = { 270.0f };
static const float S_DEG_TO_RAD_RATIO = { (float)ALLEGRO_PI / 180.0f };
static const float S_RAD_TO_DEG_RATIO = { 180.0f / (float)ALLEGRO_PI };

bool s_math_is_zero_f(float a);
bool s_math_is_equal_f(float a, float b);
float s_math_max_f(float a, float b);
float s_math_min_f(float a, float b);
float s_math_degree_to_radian(float degree);
float s_math_radian_to_degree(float radian);

#endif // !_HEADER_GUARD_LIBSPACE_MATH_H_
