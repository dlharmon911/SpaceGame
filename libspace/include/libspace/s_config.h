#ifndef _HEADER_GUARD_LIBSPACE_CONFIG_H_
#define _HEADER_GUARD_LIBSPACE_CONFIG_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"

const char* s_config_get_value_as_string(const ALLEGRO_CONFIG* config, const char* section, const char* key, const char* default_value);
bool s_config_get_value_as_bool(const ALLEGRO_CONFIG* config, const char* section, const char* key, bool default_value);
int8_t s_config_get_value_as_int8(const ALLEGRO_CONFIG* config, const char* section, const char* key, int8_t default_value);
int16_t s_config_get_value_as_int16(const ALLEGRO_CONFIG* config, const char* section, const char* key, int16_t default_value);
int32_t s_config_get_value_as_int32(const ALLEGRO_CONFIG* config, const char* section, const char* key, int32_t default_value);
int64_t s_config_get_value_as_int64(const ALLEGRO_CONFIG* config, const char* section, const char* key, int64_t default_value);
uint8_t s_config_get_value_as_uint8(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint8_t default_value);
uint16_t s_config_get_value_as_uint16(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint16_t default_value);
uint32_t s_config_get_value_as_uint32(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint32_t default_value);
uint64_t s_config_get_value_as_uint64(const ALLEGRO_CONFIG* config, const char* section, const char* key, uint64_t default_value);
float s_config_get_value_as_float(const ALLEGRO_CONFIG* config, const char* section, const char* key, float default_value);
double s_config_get_value_as_double(const ALLEGRO_CONFIG* config, const char* section, const char* key, double default_value);

void s_config_set_value_as_string(ALLEGRO_CONFIG* config, const char* section, const char* key, const char* value);
void s_config_set_value_as_bool(ALLEGRO_CONFIG* config, const char* section, const char* key, bool value);
void s_config_set_value_as_int8(ALLEGRO_CONFIG* config, const char* section, const char* key, int8_t value);
void s_config_set_value_as_int16(ALLEGRO_CONFIG* config, const char* section, const char* key, int16_t value);
void s_config_set_value_as_int32(ALLEGRO_CONFIG* config, const char* section, const char* key, int32_t value);
void s_config_set_value_as_int64(ALLEGRO_CONFIG* config, const char* section, const char* key, int64_t value);
void s_config_set_value_as_uint8(ALLEGRO_CONFIG* config, const char* section, const char* key, uint8_t value);
void s_config_set_value_as_uint16(ALLEGRO_CONFIG* config, const char* section, const char* key, uint16_t value);
void s_config_set_value_as_uint32(ALLEGRO_CONFIG* config, const char* section, const char* key, uint32_t value);
void s_config_set_value_as_uint64(ALLEGRO_CONFIG* config, const char* section, const char* key, uint64_t value);
void s_config_set_value_as_float(ALLEGRO_CONFIG* config, const char* section, const char* key, float value);
void s_config_set_value_as_double(ALLEGRO_CONFIG* config, const char* section, const char* key, double value);

#endif // !_HEADER_GUARD_LIBSPACE_CONFIG_H_
