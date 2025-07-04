#ifndef _HEADER_GUARD_LIBSPACE_CLIP_H_
#define _HEADER_GUARD_LIBSPACE_CLIP_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_rectangle.h"

const s_rectangle_t* s_clip_get_current_clip();
void s_clip_set_current_clip(const s_rectangle_t* clip);
void s_clip_set_current_clip_f(float x, float y, float width, float height);
void s_clip_set_current_clip_scaled(const s_rectangle_t* clip, const s_point_t* scale);
void s_clip_set_current_clip_scaled_f(float x, float y, float width, float height, const s_point_t* scale);

#endif // !_HEADER_GUARD_LIBSPACE_CLIP_H_
