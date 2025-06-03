#ifndef _HEADER_GUARD_LIBSPACE_CIRCLE_H_
#define _HEADER_GUARD_LIBSPACE_CIRCLE_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

typedef struct s_circle_t
{
	s_point_t m_center;
	float m_radius;
} s_circle_t;

void s_circle_zero_initialize_data(s_circle_t* circle);
void s_circle_set(s_circle_t* circle, const s_circle_t* circle2);
void s_circle_set_p(s_circle_t* circle, const s_point_t* center, float radius);
void s_circle_draw(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color, float thickness);
void s_circle_draw_filled(const s_circle_t* circle, float x, float y, ALLEGRO_COLOR color);

#endif // !_HEADER_GUARD_LIBSPACE_CIRCLE_H_
