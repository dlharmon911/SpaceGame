#ifndef _HEADER_GUARD_LIBSPACE_VIEWPORT_H_
#define _HEADER_GUARD_LIBSPACE_VIEWPORT_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_VIEWPORT_FLOAT_SIZE = S_POINT_FLOAT_SIZE + S_POINT_FLOAT_SIZE
};

typedef struct s_viewport_t
{
	union
	{
		struct
		{
			s_point_t m_point;
			s_point_t m_size;
		};
		float m_float_array[S_VIEWPORT_FLOAT_SIZE];
	};
} s_viewport_t;

void s_viewport_zero_initialize_data(s_viewport_t* viewport);
void s_viewport_set(s_viewport_t* viewport, const s_viewport_t* viewport2);
void s_viewport_set_p(s_viewport_t* viewport, const s_point_t* point, const s_point_t* size);
void s_viewport_translate(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport);
void s_viewport_scale(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport, const s_point_t* original_size);

#endif // !_HEADER_GUARD_LIBSPACE_VIEWPORT_H_
