#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"

static void g_texture_generate_radar_background(float x, float y, float width, float height)
{
	float radius = floorf(width * 0.5f);
	s_point_t center = { 0.0f, 0.0f };

	s_point_set_f(&center, x + width * 0.5f, y + height * 0.5f);

	al_draw_filled_circle(center.m_x, center.m_y, radius, al_map_rgb(0, 15, 0));
}

static void g_texture_generate_radar_sweep(float x, float y, float width, float height)
{
	s_point_t center = { 0.0f, 0.0f };
	s_point_t outer = { 0.0f, 0.0f };
	s_point_t outer2 = { 0.0f, 0.0f };
	float radius = floorf(width * 0.5f);
	float angle = 0.0f;
	float color = 0.0f;
	float arc = 1.0f / 180.0f;
	float start = 0.05f;

	s_point_set_f(&center, x + width * 0.5f, y + height * 0.5f);
	s_point_set(&outer, &center);
	s_point_add_f(&outer, width * 0.5f, 0.0f);

	al_draw_filled_circle(center.m_x, center.m_y, radius, al_map_rgb(255,0, 255));

	for (int32_t i = -90; i <= 90; ++i)
	{
		angle = (float)i * S_PI_DOUBLE / 360.0f;
		s_point_set(&outer2, &center);
		s_point_add_f(&outer2, radius * cosf(angle), radius * sinf(angle));

		color += arc;

		al_draw_filled_triangle(center.m_x, center.m_y, outer2.m_x, outer2.m_y, outer.m_x, outer.m_y, al_map_rgb_f(0.0f, s_math_min_f(1.0f, start + color), 0.0f));
		s_point_set(&outer, &outer2);
	}
}

static void g_texture_generate_radar_overlay(float x, float y, float width, float height)
{
	float radius = floorf(width * 0.5f);

	al_draw_line(x + width * 0.5f, y, x + width * 0.5f, y + height, al_map_rgb(192, 192, 192), 1.0f);
	al_draw_line(x, y + height * 0.5f, x + width, y + height * 0.5f, al_map_rgb(192, 192, 192), 1.0f);

	al_draw_circle(x + width * 0.5f, y + height * 0.5f, radius, al_map_rgb(35, 149, 0), 1.0f);
	al_draw_circle(x + width * 0.5f, y + height * 0.5f, radius - 1.0f, al_map_rgb(0, 255, 0), 1.0f);
}

static void g_texture_generate_radar_icon(float x, float y, float width, float height)
{
	float radius = 4.0f;

	for (uint32_t i = 55; i <= 255; i += 50)
	{
		al_draw_filled_circle(x + width * 0.5f, y + height * 0.5f, radius - 1, al_map_rgb(0, (uint8_t)i, 0));
		radius -= 0.5f;
	}
}

int32_t g_texture_generate_radar_texture(ALLEGRO_BITMAP** bitmap)
{
	if (!bitmap)
	{
		return -1;
	}

	s_log_print("Generating star bitmap - ");

	*bitmap = al_create_bitmap((int32_t)G_TEXTURE_RADAR_SIZE.m_x, (int32_t)G_TEXTURE_RADAR_SIZE.m_y);

	if (!*bitmap)
	{
		s_log_println("failed!");
		return -1;
	}

	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	al_set_target_bitmap(*bitmap);

	al_clear_to_color(S_COLOR_MAGIC_PINK.m_al_color);

	s_point_t half_size = { 0.0f, 0.0f };

	s_point_set(&half_size, &G_TEXTURE_RADAR_SIZE);
	s_point_multiply_f(&half_size, 0.5f);

	g_texture_generate_radar_background(0.0f, 0.0f, half_size.m_x, half_size.m_y);
	g_texture_generate_radar_sweep(0.0f, half_size.m_y, half_size.m_x, half_size.m_y);
	g_texture_generate_radar_overlay(half_size.m_x, 0.0f, half_size.m_x, half_size.m_y);
	g_texture_generate_radar_icon(half_size.m_x, half_size.m_y, 16.0f, 16.0f);



	al_set_target_bitmap(target);

	al_convert_mask_to_alpha(*bitmap, S_COLOR_MAGIC_PINK.m_al_color);

	s_log_println("passed!");

	return 0;
}
