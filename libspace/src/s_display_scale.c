#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"
#include "libspace/s_display_scale.h"

static s_point_t* _s_display_scale_get()
{
	static s_point_t scale = { 1.0f, 1.0f };

	return &scale;
}

const s_point_t* s_display_scale_get()
{
	return _s_display_scale_get();
}

void s_display_scale_reset()
{
	s_point_set_f(_s_display_scale_get(), 1.0f, 1.0f);
}

void s_display_scale_set(const s_point_t* scale)
{
	s_point_set(_s_display_scale_get(), scale);
}

void s_display_scale_set_f(float x, float y)
{
	s_point_set_f(_s_display_scale_get(), x, y);
}
