#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "libspace/s_base.h"
#include "libspace/s_log.h"
#include "libspace/s_string.h"

enum
{
	S_LOG_STRING_ARRAY_MAX_SIZE = 2048
};

static ALLEGRO_FILE** s_log_get_file()
{
	static ALLEGRO_FILE* p_file = NULL;

	return &p_file;
}

void s_log_open(const char* filename)
{
	ALLEGRO_FILE** p_file = s_log_get_file();

	if (!p_file)
	{
		return;
	}

	*p_file = al_fopen(filename, "wb");
}

bool s_log_is_open()
{
	ALLEGRO_FILE** p_file = s_log_get_file();

	if (!p_file)
	{
		return false;
	}

	return (*p_file) != NULL;
}

void s_log_close()
{
	ALLEGRO_FILE** p_file = s_log_get_file();

	if (!p_file)
	{
		return;
	}

	if (!(*p_file))
	{
		return;
	}
	
	al_fclose((*p_file));
	(*p_file) = NULL;
}

void s_log_write_buffer(const char* buffer, size_t size)
{
	ALLEGRO_FILE** p_file = s_log_get_file();

	if (!p_file)
	{
		return;
	}

	if (!(*p_file))
	{
		return;
	}

	for (size_t i = 0; i < size; ++i)
	{
		char c = *(buffer + i);
		al_fputc((*p_file), (int32_t)c);
	}
}

void s_log_flush()
{
	ALLEGRO_FILE** p_file = s_log_get_file();

	if (!p_file)
	{
		return;
	}

	if (!(*p_file))
	{
		return;
	}

	al_fflush((*p_file));
}

void s_log_print(const char* message)
{
	if (message)
	{
		size_t len = s_string_get_length(message);
		s_log_write_buffer(message, len);
	}
}

void s_log_println(const char* message)
{
	if (message)
	{
		size_t len = s_string_get_length(message);
		s_log_write_buffer(message, len);
		s_log_write_buffer("\n", 1);
	}
}

void s_log_print_bool(bool value)
{
	if (value)
	{
		s_log_print(S_STRING_TRUE);
	}
	else
	{
		s_log_print(S_STRING_FALSE);
	}
}

void s_log_print_uint_8(uint8_t value)
{
	s_log_printf("%u", (uint32_t)value);
}

void s_log_print_uint_16(uint16_t value)
{
	s_log_printf("%u", (uint32_t)value);
}

void s_log_print_uint_32(uint32_t value)
{
	s_log_printf("%u", value);
}

void s_log_print_uint_64(uint64_t value)
{
	s_log_printf("%llu", value);
}

void s_log_print_int_8(int8_t value)
{
	s_log_printf("%d", (int32_t)value);
}

void s_log_print_int_16(int16_t value)
{
	s_log_printf("%d", (int32_t)value);
}

void s_log_print_int_32(int32_t value)
{
	s_log_printf("%d", value);
}

void s_log_print_int_64(int64_t value)
{
	s_log_printf("%lld", value);
}

void s_log_print_float(float value)
{
	s_log_printf("%f", value);
}

void s_log_print_double(double value)
{
	s_log_printf("%lf", value);
}

void s_log_print_long_double(long double value)
{
	s_log_printf("%Lf", value);
}

void s_log_print_char(char c)
{
	s_log_printf("%c", c);
}

void s_log_print_vargs(const char* const format, va_list va_arg_list)
{
	static char buffer[S_LOG_STRING_ARRAY_MAX_SIZE];

	buffer[0] = 0;

	vsnprintf(buffer, S_LOG_STRING_ARRAY_MAX_SIZE, format, va_arg_list);

	s_log_print(buffer);
}

void s_log_printf(const char* const format, ...)
{
	static va_list va_arg_list;
	static char buffer[S_LOG_STRING_ARRAY_MAX_SIZE];

	buffer[0] = 0;

	va_start(va_arg_list, format);
	s_log_print_vargs(format, va_arg_list);
	va_end(va_arg_list);

	s_log_print(buffer);
}
