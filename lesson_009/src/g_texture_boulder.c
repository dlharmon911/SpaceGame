#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"

static const ALLEGRO_COLOR G_COLOR_BOULDER = { 0.34901963f, 0.235294119f, 0.141176477f, 1.0f };

static void bitmaps_texturize_bitmap()
{
	ALLEGRO_COLOR list[6] =
	{ G_COLOR_BOULDER,
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 0.0f, 1.0f}
	};
	float base = 0.75f;
	float light = 1.2f;

	for (int32_t i = 1; i < 5; ++i)
	{
		float a = ((float)i - 1) / 5.0f;

		list[i].r = list[0].r * (base + ((1.0f - base) * a));
		list[i].g = list[0].g * (base + ((1.0f - base) * a));
		list[i].b = list[0].b * (base + ((1.0f - base) * a));
	}

	list[5].r = s_math_min_f(1.0f, list[0].r * light);
	list[5].g = s_math_min_f(1.0f, list[0].g * light);
	list[5].b = s_math_min_f(1.0f, list[0].b * light);

	for (int32_t j = 0; j < (int32_t)G_TEXTURE_BOULDER_SIZE.m_y; ++j)
	{
		for (int32_t i = 0; i < (int32_t)G_TEXTURE_BOULDER_SIZE.m_x; ++i)
		{
			uint32_t r = s_random_generate(99);
			int32_t c = 5;

			if (r < 50)
			{
				c = r / 10;
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

	bitmaps_texturize_bitmap(*bitmap);
	al_unlock_bitmap(*bitmap);

	al_set_target_bitmap(target);

	s_log_println("passed!");

	return 0;
}
