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

	for (size_t i = 0; i < S_VIEWPORT_FLOAT_SIZE; ++i)
	{
		viewport->m_float_array[i] = 0.0f;
	}
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
	s_point_t translate_amount = { 0.0f, 0.0f };

	if (!transform)
	{
		return;
	}

	if (!viewport)
	{
		return;
	}

	s_point_set(&translate_amount, &viewport->m_size);
	s_point_multiply_f(&translate_amount, 0.5f);
	s_point_add(&translate_amount, &viewport->m_point);

	al_translate_transform(transform, translate_amount.m_x, translate_amount.m_y);
}

void s_viewport_scale(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport, const s_point_t* original_size)
{
	s_point_t scale_amount = { 0.0f, 0.0f };

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

	s_point_set(&scale_amount, &viewport->m_size);
	s_point_divide(&scale_amount, original_size);

	al_scale_transform(transform, scale_amount.m_x, scale_amount.m_y);
}
