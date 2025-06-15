#ifndef _HEADER_GUARD_LIBSPACE_POINT_H_
#define _HEADER_GUARD_LIBSPACE_POINT_H_

#include <stdint.h>
#include "libspace/s_base.h"

enum
{
	S_POINT_FLOAT_SIZE = 2
};

typedef struct s_point_t
{
	union {
		struct {
			float m_x;
			float m_y;
		};
		float m_float_array[S_POINT_FLOAT_SIZE];
	};
} s_point_t;

void s_point_zero_initialize_data(s_point_t* point);
void s_point_add_f(s_point_t* point, float x, float y);
void s_point_subtract_f(s_point_t* point, float x, float y);
void s_point_multiply_f(s_point_t* point, float scale);
void s_point_divide_f(s_point_t* point, float scale);
bool s_point_equals_f(const s_point_t* point, float x, float y);
void s_point_set_f(s_point_t* point, float x, float y);
void s_point_add(s_point_t* point, const s_point_t* point2);
void s_point_subtract(s_point_t* point, const s_point_t* point2);
void s_point_multiply(s_point_t* point, const s_point_t* point2);
void s_point_divide(s_point_t* point, const s_point_t* point2);
bool s_point_equals(const s_point_t* point, const s_point_t* point2);
void s_point_set(s_point_t* point, const s_point_t* point2);
void s_point_rotate(s_point_t* point, float angle);
void s_point_rotate_array(s_point_t* point, size_t count, float angle);
void s_point_set_zero(s_point_t* point);
void s_point_get_difference(s_point_t* result, const s_point_t* point, const s_point_t* point2);
float s_point_get_length(const s_point_t* point);
float s_point_get_distance_between(const s_point_t* point, const s_point_t* point2);
float s_point_dot_product(const s_point_t* point, const s_point_t* point2);
void s_point_normalize(s_point_t* result, const s_point_t* point);
void s_point_find_point_on_line(s_point_t* result, const s_point_t* point, const s_point_t* line_point1, const s_point_t* line_point2);
float s_point_line_point_distance(const s_point_t* point, const s_point_t* lpoint1, const s_point_t* lpoint2);
void s_point_translate(ALLEGRO_TRANSFORM* transform, const s_point_t* point);
void s_point_translate_f(ALLEGRO_TRANSFORM* transform, float x, float y);
void s_point_scale(ALLEGRO_TRANSFORM* transform, const s_point_t* point);

#endif // !_HEADER_GUARD_LIBSPACE_POINT_H_
