#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "libspace/s_base.h"
#include "libspace/s_string.h"
#include "libspace/s_config.h"

#define S_STRING_MAX_SIZE 128

const char* s_config_get_value_as_string(const ALLEGRO_CONFIG* config, const char* section, const char* key, const char* default_value)
{
	if (!config)
	{
		return NULL;
	}

	const char* value = al_get_config_value(config, section, key);

	if (!value)
	{
		value = default_value;
	}

	return value;
}

bool s_config_get_value_as_bool(const ALLEGRO_CONFIG* config, const char* section, const char* key, bool default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	bool rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_bool(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_bool(s);
	}

	return rv;
}

int8_t s_config_get_value_as_int8(const ALLEGRO_CONFIG* config, const char* section, const char* key, int8_t default_value)
{
	return (int8_t)s_config_get_value_as_int32(config, section, key, (int32_t)default_value);
}

int16_t s_config_get_value_as_int16(const ALLEGRO_CONFIG* config, const char* section, const char* key, int16_t default_value)
{
	return (int16_t)s_config_get_value_as_int32(config, section, key, (int32_t)default_value);
}

int32_t s_config_get_value_as_int32(const ALLEGRO_CONFIG* config, const char* section, const char* key, int32_t default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	int32_t rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_int32(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_int32(s);
	}

	return rv;
}

int64_t s_config_get_value_as_int64(const ALLEGRO_CONFIG* config, const char* section, const char* key, int64_t default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	int64_t rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_int64(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_uint64(s);
	}

	return rv;
}

uint8_t s_config_get_value_as_uint8(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint8_t default_value)
{
	return (uint8_t)s_config_get_value_as_uint32(config, section, key, (uint32_t)default_value);
}

uint16_t s_config_get_value_as_uint16(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint16_t default_value)
{
	return (uint16_t)s_config_get_value_as_uint32(config, section, key, (uint32_t)default_value);
}

uint32_t s_config_get_value_as_uint32(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint32_t default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	uint32_t rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_uint32(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_uint32(s);
	}

	return rv;
}

uint64_t s_config_get_value_as_uint64(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint64_t default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	uint64_t rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_uint64(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_uint64(s);
	}

	return rv;
}

float s_config_get_value_as_float(const ALLEGRO_CONFIG* config, const char* section, const char* key, float default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	float rv = default_value;

	if (!config)
	{
		return 0.0f;
	}

	if (!key)
	{
		return 0.0f;
	}

	s_string_set_as_float(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_float(s);
	}

	return rv;
}

double s_config_get_value_as_double(const ALLEGRO_CONFIG* config, const char* section, const char* key, double default_value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };
	double rv = default_value;

	if (!config)
	{
		return 0.0;
	}

	if (!key)
	{
		return 0.0;
	}

	s_string_set_as_double(out_value, S_STRING_MAX_SIZE, default_value);

	const char* s = al_get_config_value(config, section, key);

	if (s)
	{
		rv = s_string_get_as_double(s);
	}

	return rv;
}

/******************************************/

void s_config_set_value_as_string(ALLEGRO_CONFIG* config, const char* section, const char* key, const char* value)
{
	if (!config)
	{
		return;
	}

	if (!key)
	{
		return;
	}

	if (!value)
	{
		return;
	}

	al_set_config_value(config, section, key, value);
}

void s_config_set_value_as_bool(ALLEGRO_CONFIG* config, const char* section, const char* key, bool value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_bool(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_int8(ALLEGRO_CONFIG* config, const char* section, const char* key, int8_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_int8(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_int16(ALLEGRO_CONFIG* config, const char* section, const char* key, int16_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_int16(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_int32(ALLEGRO_CONFIG* config, const char* section, const char* key, int32_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_int32(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_int64(ALLEGRO_CONFIG* config, const char* section, const char* key, int64_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_int64(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_uint8(ALLEGRO_CONFIG* config, const char* section, const char* key, uint8_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_uint8(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_uint16(ALLEGRO_CONFIG* config, const char* section, const char* key, uint16_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_uint16(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_uint32(ALLEGRO_CONFIG* config, const char* section, const char* key, uint32_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_uint32(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_uint64(ALLEGRO_CONFIG* config, const char* section, const char* key, uint64_t value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_uint64(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_float(ALLEGRO_CONFIG* config, const char* section, const char* key, float value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_float(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}

void s_config_set_value_as_double(ALLEGRO_CONFIG* config, const char* section, const char* key, double value)
{
	char out_value[S_STRING_MAX_SIZE] = { 0 };

	s_string_set_as_double(out_value, S_STRING_MAX_SIZE, value);

	s_config_set_value_as_string(config, section, key, out_value);
}
