#ifndef _HEADER_GUARD_LIBSPACE_RECTANGLE_H_
#define _HEADER_GUARD_LIBSPACE_RECTANGLE_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_RECTANGLE_FLOAT_SIZE = S_POINT_FLOAT_SIZE + S_POINT_FLOAT_SIZE
};

typedef struct s_rectangle_t
{
	union
	{
		struct
		{
			s_point_t m_point;
			s_point_t m_size;
		};
		float m_float_array[S_RECTANGLE_FLOAT_SIZE];
	};
} s_rectangle_t;

void s_rectangle_set_zero(s_rectangle_t* rectangle);
void s_rectangle_set(s_rectangle_t* rectangle, const s_rectangle_t* rectangle2);
void s_rectangle_set_p(s_rectangle_t* rectangle, const s_point_t* point, const s_point_t* size);

#endif // !_HEADER_GUARD_LIBSPACE_RECTANGLE_H_
