#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include "libspace/s_base.h"
#include "libspace/s_string.h"

static const int32_t S_STRING_NUMBER_BASE = 10;

bool s_string_compare(const char* string1, const char* string2)
{
	if (!string1)
	{
		return 0;
	}

	if (!string2)
	{
		return 0;
	}

	while (*string1 && *string2)
	{
		if (*string1 != *string2)
		{
			return false;
		}

		++string1;
		++string2;
	}

	return (*string1 == *string2);
}

bool s_string_compare_ignore_case(const char* string1, const char* string2)
{
	if (!string1)
	{
		return 0;
	}

	if (!string2)
	{
		return 0;
	}

	while (*string1 && *string2)
	{
		if (tolower(*string1) != tolower(*string2))
		{
			return false;
		}

		++string1;
		++string2;
	}

	return (*string1 == *string2);
}

size_t s_string_get_length(const char* string)
{
	const char* start = string;

	if (!string)
	{
		return 0;
	}

	while (*string)
	{
		++string;
	}

	return (size_t)(string - start);
}

bool s_string_get_as_bool(const char* string)
{
	if (!string)
	{
		return false;
	}

	if (string[0] == 0)
	{
		return false;
	}

	size_t index = 0;

	while (S_STRING_TRUE[index])
	{
		if (tolower(string[index]) != S_STRING_TRUE[index])
		{
			return false;
		}

		++index;
	}

	return true;
}

int8_t s_string_get_as_int8(const char* string)
{
	return (int8_t)s_string_get_as_int32(string);
}

int16_t s_string_get_as_int16(const char* string)
{
	return (int16_t)s_string_get_as_int32(string);
}

int32_t s_string_get_as_int32(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	int32_t value = strtol(string, &endptr, S_STRING_NUMBER_BASE);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

int64_t s_string_get_as_int64(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	int64_t value = strtoll(string, &endptr, S_STRING_NUMBER_BASE);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

uint8_t s_string_get_as_uint8(const char* string)
{
	return (uint8_t)s_string_get_as_uint32(string);
}

uint16_t s_string_get_as_uint16(const char* string)
{
	return (uint16_t)s_string_get_as_uint32(string);
}

uint32_t s_string_get_as_uint32(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	uint32_t value = strtoul(string, &endptr, S_STRING_NUMBER_BASE);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

uint64_t s_string_get_as_uint64(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	uint64_t value = strtoull(string, &endptr, S_STRING_NUMBER_BASE);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

float s_string_get_as_float(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	float value = strtof(string, &endptr);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

double s_string_get_as_double(const char* string)
{
	char* endptr = NULL;

	if (!string)
	{
		return 0;
	}

	if (string[0] == 0)
	{
		return 0;
	}

	double value = strtod(string, &endptr);

	if (endptr && *endptr != 0)
	{
		return 0;
	}

	return value;
}

void s_string_set_as_bool(char* string, size_t length, bool value)
{
	sprintf_s(string, length, "%s", (value ? S_STRING_TRUE : S_STRING_FALSE));
}

void s_string_set_as_int8(char* string, size_t length, int8_t value)
{
	s_string_set_as_int32(string, length, (int32_t)value);
}

void s_string_set_as_int16(char* string, size_t length, int16_t value)
{
	s_string_set_as_int32(string, length, (int32_t)value);
}

void s_string_set_as_int32(char* string, size_t length, int32_t value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%d", value);
}

void s_string_set_as_int64(char* string, size_t length, int64_t value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%lld", value);
}

void s_string_set_as_uint8(char* string, size_t length, uint8_t value)
{
	s_string_set_as_uint32(string, length, (uint32_t)value);
}

void s_string_set_as_uint16(char* string, size_t length, uint16_t value)
{
	s_string_set_as_uint32(string, length, (uint32_t)value);
}

void s_string_set_as_uint32(char* string, size_t length, uint32_t value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%u", value);
}

void s_string_set_as_uint64(char* string, size_t length, uint64_t value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%llu", value);
}

void s_string_set_as_float(char* string, size_t length, float value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%f", value);
}

void s_string_set_as_double(char* string, size_t length, double value)
{
	if (!string)
	{
		return;
	}

	sprintf_s(string, length, "%lf", value);
}
