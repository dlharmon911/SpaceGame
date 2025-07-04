#ifndef _HEADER_GUARD_LIBSPACE_STRING_H_
#define _HEADER_GUARD_LIBSPACE_STRING_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include <string.h>
#include "libspace/s_base.h"

bool s_string_compare(const char* string1, const char* string2);
bool s_string_compare_ignore_case(const char* string1, const char* string2);
size_t s_string_get_length(const char* string);

bool s_string_get_as_bool(const char* string);
int8_t s_string_get_as_int8(const char* string);
int16_t s_string_get_as_int16(const char* string);
int32_t s_string_get_as_int32(const char* string);
int64_t s_string_get_as_int64(const char* string);
uint8_t s_string_get_as_uint8(const char* string);
uint16_t s_string_get_as_uint16(const char* string);
uint32_t s_string_get_as_uint32(const char* string);
uint64_t s_string_get_as_uint64(const char* string);
float s_string_get_as_float(const char* string);
double s_string_get_as_double(const char* string);

void s_string_set_as_bool(char* string, size_t length, bool value);
void s_string_set_as_int8(char* string, size_t length, int8_t value);
void s_string_set_as_int16(char* string, size_t length, int16_t value);
void s_string_set_as_int32(char* string, size_t length, int32_t value);
void s_string_set_as_int64(char* string, size_t length, int64_t value);
void s_string_set_as_uint8(char* string, size_t length, uint8_t value);
void s_string_set_as_uint16(char* string, size_t length, uint16_t value);
void s_string_set_as_uint32(char* string, size_t length, uint32_t value);
void s_string_set_as_uint64(char* string, size_t length, uint64_t value);
void s_string_set_as_float(char* string, size_t length, float value);
void s_string_set_as_double(char* string, size_t length, double value);

#endif // !_HEADER_GUARD_LIBSPACE_STRING_H_
