#ifndef _HEADER_GUARD_LIBSPACE_DISPLAY_SCALE_H_
#define _HEADER_GUARD_LIBSPACE_DISPLAY_SCALE_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

const s_point_t* s_display_scale_get();
void s_display_scale_reset();
void s_display_scale_set(const s_point_t* scale);
void s_display_scale_set_f(float x, float y);

#endif // !_HEADER_GUARD_LIBSPACE_DISPLAY_SCALE_H_
