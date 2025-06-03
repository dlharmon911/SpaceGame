#ifndef _HEADER_GUARD_LIBSPACE_RANDOM_H_
#define _HEADER_GUARD_LIBSPACE_RANDOM_H_

#include <stdlib.h>
#include <stdint.h>
#include "libspace/s_base.h"

void s_random_set_seed(uint32_t seed);
uint32_t s_random_generate(uint32_t limit);
uint32_t s_random_generate_constraint(uint32_t lower_limit, uint32_t upper_limit);
float s_random_generate_f(float limit);
float s_random_generate_constraint_f(float lower_limit, float upper_limit);

#endif // !_HEADER_GUARD_LIBSPACE_RANDOM_H_
