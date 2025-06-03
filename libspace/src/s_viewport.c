#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_viewport.h"

void s_viewport_zero_initialize_data(s_viewport_t* viewport)
{
	if (!viewport)
	{
		return;
	}

	s_point_zero_initialize_data(&viewport->m_point);
	s_point_zero_initialize_data(&viewport->m_size);
}

void s_viewport_set(s_viewport_t* viewport, const s_viewport_t* viewport2)
{
	if (!viewport)
	{
		return;
	}

	if (!viewport2)
	{
		return;
	}

	for (size_t i = 0; i < S_VIEWPORT_FLOAT_SIZE; ++i)
	{
		viewport->m_float_array[i] = viewport2->m_float_array[i];
	}
}
void s_viewport_set_p(s_viewport_t* viewport, const s_point_t* point, const s_point_t* size)
{
	if (!viewport)
	{
		return;
	}

	s_point_set(&viewport->m_point, point);
	s_point_set(&viewport->m_size, size);
}

void s_viewport_translate(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport)
{
	if (!transform)
	{
		return;
	}

	if (!viewport)
	{
		return;
	}

	al_translate_transform(transform, viewport->m_point.m_x + viewport->m_size.m_x * 0.5f, viewport->m_point.m_y + viewport->m_size.m_y * 0.5f);
}

void s_viewport_scale(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport, const s_point_t* original_size)
{
	if (!transform)
	{
		return;
	}

	if (!viewport)
	{
		return;
	}

	if (!original_size)
	{
		return;
	}

	al_scale_transform(transform, viewport->m_size.m_x / original_size->m_x, viewport->m_size.m_y / original_size->m_y);
}
