#include <stdlib.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_random.h"

void s_random_set_seed(uint32_t seed)
{
	srand(seed);
}

uint32_t s_random_generate(uint32_t limit)
{
	return rand() % (limit + 1);
}

uint32_t s_random_generate_constraint(uint32_t lower_limit, uint32_t upper_limit)
{
	return lower_limit + s_random_generate(upper_limit - lower_limit);
}

float s_random_generate_f(float limit)
{
	return (float)(rand()) / ((float)(RAND_MAX) / limit);
}

float s_random_generate_constraint_f(float lower_limit, float upper_limit)
{
	return lower_limit + s_random_generate_f(upper_limit - lower_limit);
}
