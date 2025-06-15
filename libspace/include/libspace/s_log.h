#ifndef _HEADER_GUARD_LIBSPACE_LOG_H_
#define _HEADER_GUARD_LIBSPACE_LOG_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include "libspace/s_base.h"

/// <summary>Open a file to be able to output application status</summary>
/// <param name='filename'> - name of the file</param>
/// <returns>n/a - no return value</returns>
void s_log_open(const char* filename);

/// <summary>Query if the log file open</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>bool - returns true if log is open or false on error</returns>
bool s_log_is_open();

/// <summary>Closed the log file</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return value</returns>
void s_log_close();

/// <summary>Flush the log file</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return value</returns>
void s_log_flush();

/// <summary>Closed the log file</summary>
/// <param name='buffer'> - data to write</param>
/// <param name='size'> - byte count of buffer data</param>
/// <returns>n/a - no return value</returns>
void s_log_write_buffer(const char* buffer, size_t size);

/// <summary>Write a string to the log file</summary>
/// <param name='message'> - string buffer to output</param>
/// <returns>n/a - no return value</returns>
void s_log_print(const char* message);

/// <summary>Write a string to the log file with a trailing new line character</summary>
/// <param name='message'> - string buffer to output</param>
/// <returns>n/a - no return value</returns>
void s_log_println(const char* message);

/// <summary>Write a string S_STRING_TRUE or S_STRING_FALSE depending on boolean value</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_bool(bool value);

/// <summary>Write a uint8_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_uint_8(uint8_t value);

/// <summary>Write a uint16_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_uint_16(uint16_t value);

/// <summary>Write a uint32_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_uint_32(uint32_t value);

/// <summary>Write a uint64_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_uint_64(uint64_t value);

/// <summary>Write a int8_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_int_8(int8_t value);

/// <summary>Write a int16_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_int_16(int16_t value);

/// <summary>Write a int32_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_int_32(int32_t value);

/// <summary>Write a int64_t value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_int_64(int64_t value);

/// <summary>Write a float value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_float(float value);

/// <summary>Write a double value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_double(double value);

/// <summary>Write a long double value to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_long_double(long double value);

/// <summary>Write a character to the log file</summary>
/// <param name='value'> - value output</param>
/// <returns>n/a - no return value</returns>
void s_log_print_char(char c);

/// <summary>Write a formatted string to the log file</summary>
/// <param name='format'> - format specifier</param>
/// <param name='va_arg_list'> - variadic arguments</param>
/// <returns>n/a - no return value</returns>
void s_log_print_vargs(const char* const format, va_list va_arg_list);

/// <summary>Write a formatted string to the log file</summary>
/// <param name='format'> - format specifier</param>
/// <param name='...'> - arguments if any</param>
/// <returns>n/a - no return value</returns>
void s_log_printf(const char* const format, ...);

#endif // !_HEADER_GUARD_LIBSPACE_LOG_H_
