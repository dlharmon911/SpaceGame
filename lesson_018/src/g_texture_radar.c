#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_texture_data.h"

static const ALLEGRO_COLOR G_RADAR_COLOR_SHADE = { 0.0f, 1.0f, 0.0f, 1.0f };
static const float G_RADAR_COLOR_CIRCLE_BACKGROUND = 0.058823529f;
static const float G_RADAR_COLOR_CIRCLE_LAYER_INSIDE = 0.13725490196f;
static const float G_RADAR_COLOR_CIRCLE_LAYER_OUTSIDE = 0.8f;
static const float G_RADAR_COLOR_CROSSHAIR = 0.75294117647f;
static const float G_RADAR_COLOR_SWEEP = 1.0f;
static const float G_RADAR_CIRCLE_RADIUS = 64.0f;
static const float G_RADAR_LINE_THICKNESS = 1.0f;
static const float G_RADAR_CIRCLE_INSIDE_THICKNESS = 1.0f;
static const float G_RADAR_CIRCLE_OUTSIDE_THICKNESS = 2.0f;
static const float G_RADAR_ICON_RADIUS = 5.0f;
static const s_point_t G_RADAR_ICON_TEXTURE_SIZE = { 16.0f, 16.0f };
static const int32_t G_RADAR_SWEEP_ANGLE_START = -90;
static const int32_t G_RADAR_SWEEP_ANGLE_END = 90;
static const int32_t G_RADAR_ICON_SEGMENT_SIZE = 50;

static ALLEGRO_COLOR* g_texture_radar_shade_color(float color)
{
	static ALLEGRO_COLOR rv = { 0.0f, 0.0f, 0.0f, 1.0f };

	rv.r = color * G_RADAR_COLOR_SHADE.r;
	rv.g = color * G_RADAR_COLOR_SHADE.g;
	rv.b = color * G_RADAR_COLOR_SHADE.b;
	rv.a = 1.0f;

	return &rv;
}

static void g_texture_generate_radar_background(float center_x, float center_y, float radius)
{
	al_draw_filled_circle(center_x, center_y, radius, *g_texture_radar_shade_color(G_RADAR_COLOR_CIRCLE_BACKGROUND));
}

static void g_texture_generate_radar_sweep(float center_x, float center_y, float radius)
{
	s_point_t center = { 0.0f, 0.0f };
	s_point_t outer = { 0.0f, 0.0f };
	s_point_t outer2 = { 0.0f, 0.0f };
	float angle = 0.0f;
	float color = 0.0f;
	float arc = 1.0f / (float)(G_RADAR_SWEEP_ANGLE_END - G_RADAR_SWEEP_ANGLE_START);
	float start = G_RADAR_COLOR_CIRCLE_BACKGROUND;
	float color_map = { 0.0f };
	float factor = 0.0f;
	float sradius = radius - 1.0f;

	s_point_set_f(&center, center_x, center_y);
	s_point_set(&outer, &center);
	s_point_add_f(&outer, sradius * cosf(angle), sradius * sinf(angle));

	al_draw_filled_circle(center_x, center_y, sradius, S_COLOR_MAGIC_PINK.m_al_color);

	for (int32_t i = G_RADAR_SWEEP_ANGLE_START; i <= G_RADAR_SWEEP_ANGLE_END; ++i)
	{
		angle = s_math_degree_to_radian((float)i);
		s_point_set(&outer2, &center);
		s_point_add_f(&outer2, sradius * cosf(angle), sradius * sinf(angle));

		color += arc;

		factor = s_math_min_f(S_COLOR_COMPONENT_MAX_F, start + color);

		color_map = G_RADAR_COLOR_SWEEP * factor;

		al_draw_filled_triangle(center_x, center_y, outer2.m_x, outer2.m_y, outer.m_x, outer.m_y, *g_texture_radar_shade_color(color_map));
		s_point_set(&outer, &outer2);
	}
}

static void g_texture_generate_radar_overlay(float center_x, float center_y, float radius)
{
	al_draw_line(center_x - radius, center_y, center_x + radius, center_y, *g_texture_radar_shade_color(G_RADAR_COLOR_CROSSHAIR), G_RADAR_LINE_THICKNESS);
	al_draw_line(center_x, center_y - radius, center_x, center_y + radius, *g_texture_radar_shade_color(G_RADAR_COLOR_CROSSHAIR), G_RADAR_LINE_THICKNESS);

	al_draw_circle(center_x, center_y, radius - 1.0f, *g_texture_radar_shade_color(G_RADAR_COLOR_CIRCLE_LAYER_OUTSIDE), G_RADAR_CIRCLE_OUTSIDE_THICKNESS);
	al_draw_circle(center_x, center_y, radius, *g_texture_radar_shade_color(G_RADAR_COLOR_CIRCLE_LAYER_INSIDE), G_RADAR_CIRCLE_INSIDE_THICKNESS);
}

static void g_texture_generate_radar_icon(float x, float y, float width, float height)
{
	float radius = G_RADAR_ICON_RADIUS;
	float color_map = 0.0f;
	float factor = 0.0f;
	int32_t seg_count = S_COLOR_COMPONENT_MAX / G_RADAR_ICON_SEGMENT_SIZE;
	int32_t seg_start = S_COLOR_COMPONENT_MAX % G_RADAR_ICON_SEGMENT_SIZE;

	for (int32_t i = 0; i <= seg_count; ++i)
	{
		factor = (float)(i * G_RADAR_ICON_SEGMENT_SIZE + seg_start) / (float)S_COLOR_COMPONENT_MAX;

		color_map = G_RADAR_COLOR_SWEEP * factor;

		al_draw_filled_circle(x + width * 0.5f, y + height * 0.5f, radius - 1, *g_texture_radar_shade_color(color_map));
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

	g_texture_generate_radar_background(G_RADAR_CIRCLE_RADIUS, G_RADAR_CIRCLE_RADIUS, G_RADAR_CIRCLE_RADIUS);
	g_texture_generate_radar_sweep(G_RADAR_CIRCLE_RADIUS, half_size.m_y + G_RADAR_CIRCLE_RADIUS, G_RADAR_CIRCLE_RADIUS);
	g_texture_generate_radar_overlay(half_size.m_x + G_RADAR_CIRCLE_RADIUS, G_RADAR_CIRCLE_RADIUS, G_RADAR_CIRCLE_RADIUS);
	g_texture_generate_radar_icon(half_size.m_x, half_size.m_y, G_RADAR_ICON_TEXTURE_SIZE.m_x, G_RADAR_ICON_TEXTURE_SIZE.m_y);

	al_set_target_bitmap(target);

	al_convert_mask_to_alpha(*bitmap, S_COLOR_MAGIC_PINK.m_al_color);

	s_log_println("success");

	return 0;
}
