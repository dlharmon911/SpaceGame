#include <stdint.h>
#include <math.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_clip.h"

const s_rectangle_t* s_clip_get_current_clip()
{
	static s_rectangle_t clip = { {0.0f, 0.0f, 0.0f, 0.0f} };
	static int32_t c[S_RECTANGLE_FLOAT_SIZE] = { 0, 0, 0, 0 };

	al_get_clipping_rectangle(c, c + 1, c + 2, c + 3);

	for (size_t i = 0; i < S_RECTANGLE_FLOAT_SIZE; ++i)
	{
		clip.m_float_array[i] = (float)c[i];
	}

	return &clip;
}

void s_clip_set_current_clip(const s_rectangle_t* clip)
{
	static int32_t c[S_RECTANGLE_FLOAT_SIZE] = { 0, 0, 0, 0 };

	if (!clip)
	{
		return;
	}

	for (size_t i = 0; i < S_RECTANGLE_FLOAT_SIZE; ++i)
	{
		c[i] = (int32_t)clip->m_float_array[i];
	}

	al_set_clipping_rectangle(c[0], c[1], c[2], c[3]);
}

void s_clip_set_current_clip_f(float x, float y, float width, float height)
{
	static int32_t c[S_RECTANGLE_FLOAT_SIZE] = { 0, 0, 0, 0 };

	c[0] = (int32_t)x;
	c[1] = (int32_t)y;
	c[2] = (int32_t)width;
	c[3] = (int32_t)height;

	al_set_clipping_rectangle(c[0], c[1], c[2], c[3]);
}

void s_clip_set_current_clip_scaled(const s_rectangle_t* clip, const s_point_t* scale)
{
	static int32_t c[S_RECTANGLE_FLOAT_SIZE] = { 0, 0, 0, 0 };
	float v = 0.0f;

	if (!clip)
	{
		return;
	}

	if (!scale)
	{
		return;
	}

	for (size_t i = 0; i < S_RECTANGLE_FLOAT_SIZE; ++i)
	{
		v = clip->m_float_array[i];

		if (i & 1)
		{
			v *= fabsf(scale->m_y);
		}
		else
		{
			v *= fabsf(scale->m_x);
		}

		c[i] = (int32_t)v;
	}

	al_set_clipping_rectangle(c[0], c[1], c[2], c[3]);
}


void s_clip_set_current_clip_scaled_f(float x, float y, float width, float height, const s_point_t* scale)
{
	static int32_t c[S_RECTANGLE_FLOAT_SIZE] = { 0, 0, 0, 0 };

	if (!scale)
	{
		return;
	}

	c[0] = (int32_t)(x * fabsf(scale->m_x));
	c[1] = (int32_t)(y * fabsf(scale->m_y));
	c[2] = (int32_t)(width * fabsf(scale->m_x));
	c[3] = (int32_t)(height * fabsf(scale->m_y));

	al_set_clipping_rectangle(c[0], c[1], c[2], c[3]);
}