#ifndef _HEADER_GUARD_LIBSPACE_FLAGS_H_
#define _HEADER_GUARD_LIBSPACE_FLAGS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

uint32_t s_flags_set(uint32_t* value, uint32_t flag);
uint32_t s_flags_add(uint32_t* value, uint32_t flag);
uint32_t s_flags_remove(uint32_t* value, uint32_t flag);
uint32_t s_flags_toggle(uint32_t* value, uint32_t flag);
uint32_t s_flags_apply_mask(uint32_t value, uint32_t flag);
bool s_flags_is_set(uint32_t value, uint32_t flag);

#endif // !_HEADER_GUARD_LIBSPACE_FLAGS_H_
