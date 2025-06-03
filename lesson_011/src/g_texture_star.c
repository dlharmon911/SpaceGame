#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"

static void g_bitmaps_draw_star(float x, float y)
{
	s_color_t color = { 1.0f, 1.0f, 1.0f, 1.0f };

	color.m_red = s_random_generate_constraint_f(0.85f, 1.0f);
	color.m_green = s_random_generate_constraint_f(0.85f, 1.0f);
	color.m_blue = s_random_generate_constraint_f(0.85f, 1.0f);

	s_point_t center = { x + G_TEXTURE_STAR_CHUNK_SIZE.m_x * 0.5f, y + G_TEXTURE_STAR_CHUNK_SIZE.m_y * 0.5f };
	float diff = s_random_generate_constraint_f(G_TEXTURE_STAR_CHUNK_SIZE.m_x * 0.2f, G_TEXTURE_STAR_CHUNK_SIZE.m_x * 0.40f);
	float thickness = 2.0f + s_random_generate_f(G_TEXTURE_STAR_CHUNK_SIZE.m_x * 0.25f);

	al_draw_line(center.m_x, center.m_y - diff, center.m_x, center.m_y + diff, color.m_al_color, thickness);
	al_draw_line(center.m_x - diff, center.m_y, center.m_x + diff, center.m_y, color.m_al_color, thickness);
}

int32_t g_texture_generate_star_texture(ALLEGRO_BITMAP** bitmap)
{
	if (!bitmap)
	{
		return -1;
	}

	s_log_print("Generating star bitmap - ");

	*bitmap = al_create_bitmap((int32_t)G_TEXTURE_STAR_SIZE.m_x, (int32_t)G_TEXTURE_STAR_SIZE.m_y);

	if (!*bitmap)
	{
		s_log_println("failed!");
		return -1;
	}

	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	s_point_t point = { 0.0f, 0.0f };
	al_set_target_bitmap(*bitmap);

	al_clear_to_color(S_COLOR_MAGIC_PINK.m_al_color);

	while (point.m_y < G_TEXTURE_STAR_SIZE.m_y)
	{
		while (point.m_x < G_TEXTURE_STAR_SIZE.m_x)
		{
			g_bitmaps_draw_star(point.m_x, point.m_y);
			g_bitmaps_draw_star(point.m_x, point.m_y);
			point.m_x += G_TEXTURE_STAR_CHUNK_SIZE.m_x;
		}

		point.m_y += G_TEXTURE_STAR_CHUNK_SIZE.m_y;
		point.m_x = 0.0f;
	}
	al_set_target_bitmap(target);

	al_convert_mask_to_alpha(*bitmap, S_COLOR_MAGIC_PINK.m_al_color);

	s_log_println("passed!");

	return 0;
}
