#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_viewport.h"

void s_viewport_set_zero(s_viewport_t* viewport)
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
void s_viewport_set_p(s_viewport_t* viewport, const s_point_t* point, const s_point_t* size, const s_point_t* scale)
{
	if (!viewport)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	if (!size)
	{
		return;
	}

	if (!scale)
	{
		return;
	}

	s_point_set(&viewport->m_rectangle.m_point, point);
	s_point_set(&viewport->m_rectangle.m_size, size);
	s_point_set(&viewport->m_scale, scale);
}

static void s_viewport_translate(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport)
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

	s_point_set(&translate_amount, &viewport->m_rectangle.m_size);
	s_point_multiply_f(&translate_amount, 0.5f);
	s_point_add(&translate_amount, &viewport->m_rectangle.m_point);

	al_translate_transform(transform, translate_amount.m_x, translate_amount.m_y);
}


void s_viewport_transform(ALLEGRO_TRANSFORM* transform, const s_viewport_t* viewport)
{
	if (!transform)
	{
		return;
	}

	if (!viewport)
	{
		return;
	}
	static ALLEGRO_TRANSFORM backup;
	al_copy_transform(&backup, al_get_current_transform());

	al_identity_transform(transform);
	s_point_scale(transform, &viewport->m_scale);
	s_viewport_translate(transform, viewport);
}
