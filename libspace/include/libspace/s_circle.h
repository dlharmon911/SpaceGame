#ifndef _HEADER_GUARD_LIBSPACE_CIRCLE_H_
#define _HEADER_GUARD_LIBSPACE_CIRCLE_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_CIRCLE_FLOAT_SIZE = S_POINT_FLOAT_SIZE + 1
};

typedef struct s_circle_t
{
	union
	{
		struct
		{
			s_point_t m_center;
			float m_radius;
		};
		float m_float_array[S_CIRCLE_FLOAT_SIZE];
	};
} s_circle_t;

void s_circle_zero_initialize_data(s_circle_t* circle);
void s_circle_set(s_circle_t* circle, const s_circle_t* circle2);
void s_circle_set_p(s_circle_t* circle, const s_point_t* center, float radius);
void s_circle_draw(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color, float thickness);
void s_circle_draw_filled(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color);

#endif // !_HEADER_GUARD_LIBSPACE_CIRCLE_H_
