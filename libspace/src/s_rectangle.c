#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_rectangle.h"

void s_rectangle_set_zero(s_rectangle_t* rectangle)
{
	if (!rectangle)
	{
		return;
	}

	for (size_t i = 0; i < S_RECTANGLE_FLOAT_SIZE; ++i)
	{
		rectangle->m_float_array[i] = 0.0f;
	}
}

void s_rectangle_set(s_rectangle_t* rectangle, const s_rectangle_t* rectangle2)
{
	if (!rectangle)
	{
		return;
	}

	if (!rectangle2)
	{
		return;
	}

	for (size_t i = 0; i < S_RECTANGLE_FLOAT_SIZE; ++i)
	{
		rectangle->m_float_array[i] = rectangle2->m_float_array[i];
	}
}
void s_rectangle_set_p(s_rectangle_t* rectangle, const s_point_t* point, const s_point_t* size)
{
	if (!rectangle)
	{
		return;
	}

	s_point_set(&rectangle->m_point, point);
	s_point_set(&rectangle->m_size, size);
}

