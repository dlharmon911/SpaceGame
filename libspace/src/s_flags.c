#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_flags.h"

uint32_t s_flags_set(uint32_t* value, uint32_t flag)
{
	if (!value)
	{
		return 0;
	}

	*value = flag;

	return *value;
}

uint32_t s_flags_add(uint32_t* value, uint32_t flag)
{
	if (!value)
	{
		return 0;
	}

	*value |= flag;

	return *value;
}

uint32_t s_flags_remove(uint32_t* value, uint32_t flag)
{
	if (!value)
	{
		return 0;
	}

	*value &= ~flag;

	return *value;
}

uint32_t s_flags_toggle(uint32_t* value, uint32_t flag)
{
	if (!value)
	{
		return 0;
	}

	*value ^= flag;

	return *value;
}

uint32_t s_flags_apply_mask(uint32_t value, uint32_t flag)
{
	return (value & flag);
}

bool s_flags_is_set(uint32_t value, uint32_t flag)
{
	return (bool)(value & flag);
}
