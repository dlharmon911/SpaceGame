#ifndef _HEADER_GUARD_LIBSPACE_COLOR_H_
#define _HEADER_GUARD_LIBSPACE_COLOR_H_

#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_COLOR_FLOAT_SIZE = 4
};

typedef struct s_color_t
{
	union
	{
		struct
		{
			float m_red;
			float m_green;
			float m_blue;
			float m_alpha;
		};
		float m_float_array[S_COLOR_FLOAT_SIZE];
		ALLEGRO_COLOR m_al_color;
	};
} s_color_t;

/// <summary>Alternate for BLACK 0x16161d</summary>
static const s_color_t S_COLOR_EIGENGRAU = { 0.08627451f, 0.08627451f, 0.11372549f, 1.0f };

/// <summary>Alternate for BLACK 0x16161d</summary>
static const s_color_t S_COLOR_MAGIC_PINK = { 1.0f, 0.0f, 1.0f, 1.0f };

/// <summary>RGBA White</summary>
static const s_color_t S_COLOR_BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };

/// <summary>RGBA White</summary>
static const s_color_t S_COLOR_WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };

#endif // !_HEADER_GUARD_LIBSPACE_COLOR_H_
