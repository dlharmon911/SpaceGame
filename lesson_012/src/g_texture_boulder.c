#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"

enum
{
	G_BOULD_COLOR_ARRAY_SIZE = 6
};

static const uint32_t G_TEXTURE_BOULDER_RANDOM = 1000;
static const ALLEGRO_COLOR G_COLOR_BOULDER = { 0.34901963f, 0.235294119f, 0.141176477f, 1.0f };
static const float G_BOULDER_TEXTURE_COLOR_BASE = 0.75f;
static const float G_BOULDER_TEXTURE_COLOR_LIGHT = 1.2f;

static void g_bitmaps_texturize_bitmap()
{
	ALLEGRO_COLOR list[G_BOULD_COLOR_ARRAY_SIZE] =
	{ G_COLOR_BOULDER,
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f}
	};
	float base = G_BOULDER_TEXTURE_COLOR_BASE;
	float light = G_BOULDER_TEXTURE_COLOR_LIGHT;

	for (int32_t i = 1; i < (G_BOULD_COLOR_ARRAY_SIZE - 1); ++i)
	{
		float a = ((float)i - 1) / (float)(G_BOULD_COLOR_ARRAY_SIZE - 1);

		list[i].r = list[0].r * (base + ((1.0f - base) * a));
		list[i].g = list[0].g * (base + ((1.0f - base) * a));
		list[i].b = list[0].b * (base + ((1.0f - base) * a));
	}

	list[G_BOULD_COLOR_ARRAY_SIZE - 1].r = s_math_min_f(1.0f, list[0].r * light);
	list[G_BOULD_COLOR_ARRAY_SIZE - 1].g = s_math_min_f(1.0f, list[0].g * light);
	list[G_BOULD_COLOR_ARRAY_SIZE - 1].b = s_math_min_f(1.0f, list[0].b * light);

	for (int32_t j = 0; j < (int32_t)G_TEXTURE_BOULDER_SIZE.m_y; ++j)
	{
		for (int32_t i = 0; i < (int32_t)G_TEXTURE_BOULDER_SIZE.m_x; ++i)
		{
			uint32_t c = (G_BOULD_COLOR_ARRAY_SIZE - 1);
			uint32_t r = s_random_generate(G_TEXTURE_BOULDER_RANDOM - 1);

			if (r < (G_TEXTURE_BOULDER_RANDOM >> 1))
			{
				c = r / (G_TEXTURE_BOULDER_RANDOM / 10);
			}

			al_put_pixel(i, j, list[c]);
		}
	}
}

int32_t g_texture_generate_boulder_texture(ALLEGRO_BITMAP** bitmap)
{
	if (!bitmap)
	{
		return -1;
	}

	s_log_print("Generating boulder bitmap - ");

	*bitmap = al_create_bitmap((int32_t)G_TEXTURE_BOULDER_SIZE.m_x, (int32_t)G_TEXTURE_BOULDER_SIZE.m_y);

	if (!*bitmap)
	{
		s_log_println("failed!");
		return -1;
	}

	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	al_set_target_bitmap(*bitmap);

	al_clear_to_color(G_COLOR_BOULDER);

	const ALLEGRO_LOCKED_REGION* region = al_lock_bitmap(*bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);

	if (!region)
	{
		al_destroy_bitmap(*bitmap);
		*bitmap = NULL;
		return -1;
	}

	g_bitmaps_texturize_bitmap(*bitmap);
	al_unlock_bitmap(*bitmap);

	al_set_target_bitmap(target);

	s_log_println("passed!");

	return 0;
}
