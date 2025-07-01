#ifndef _HEADER_GUARD_LIBSPACE_TRIANGLE_H_
#define _HEADER_GUARD_LIBSPACE_TRIANGLE_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_TRIANGLE_POINT_COUNT = 3,
	S_TRIANGLE_FLOAT_ARRAY = S_TRIANGLE_POINT_COUNT * S_POINT_FLOAT_SIZE
};

typedef struct s_triangle_t
{
	union {
		struct {
			s_point_t m_point1;
			s_point_t m_point2;
			s_point_t m_point3;
		};
		s_point_t m_point_array[S_TRIANGLE_POINT_COUNT];
		float m_float_array[S_TRIANGLE_FLOAT_ARRAY];
	};
} s_triangle_t;

void s_triangle_set_zero(s_triangle_t* triangle);
void s_triangle_set_p(s_triangle_t* triangle, const s_point_t* point1, const s_point_t* point2, const s_point_t* point3);
void s_triangle_set(s_triangle_t* triangle, const s_triangle_t* triangle2);
void s_triangle_draw(const s_triangle_t* triangle, float x, float y, ALLEGRO_COLOR color, float thickness);
void s_triangle_draw_filled(const s_triangle_t* triangle, float x, float y, ALLEGRO_COLOR color);

#endif // !_HEADER_GUARD_LIBSPACE_TRIANGLE_H_
