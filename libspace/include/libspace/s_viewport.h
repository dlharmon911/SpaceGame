#ifndef _HEADER_GUARD_LIBSPACE_VIEWPORT_H_
#define _HEADER_GUARD_LIBSPACE_VIEWPORT_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_rectangle.h"

enum
{
	S_VIEWPORT_FLOAT_SIZE = S_RECTANGLE_FLOAT_SIZE + S_POINT_FLOAT_SIZE
};

typedef struct s_viewport_t
{
	union
	{
		struct
		{
			s_rectangle_t m_rectangle;
			s_point_t m_scale;
		};
		float m_float_array[S_VIEWPORT_FLOAT_SIZE];
	};
} s_viewport_t;

void s_viewport_set_zero(s_viewport_t* viewport);
void s_viewport_set(s_viewport_t* viewport, const s_viewport_t* viewport2);
void s_viewport_set_p(s_viewport_t* viewport, const s_point_t* point, const s_point_t* size, const s_point_t* scale);
void s_viewport_transform(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport);

#endif // !_HEADER_GUARD_LIBSPACE_VIEWPORT_H_
