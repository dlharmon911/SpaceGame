#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"
#include "libspace/s_color.h"

void s_color_set_zero(s_color_t* color)
{
	if (!color)
	{
		return;
	}

	for (size_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
	{
		color->m_float_array[i] = 0.0f;
	}
}

