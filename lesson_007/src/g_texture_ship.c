#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"

/// <summary>Color of the ship's outer hull</summary>
static const ALLEGRO_COLOR G_COLOR_SHIP_HULL = { 1.0f, 1.0f, 0.0f, 1.0f };

/// <summary>Color of the vertical center line</summary>
static const ALLEGRO_COLOR G_COLOR_SHIP_CENTER_LINE = { 0.8f, 0.8f, 0.2f, 1.0f };

/// <summary>Color of the ship's outer border</summary>
static const ALLEGRO_COLOR G_COLOR_SHIP_OUTLINE = { 1.0f, 0.65f, 0.0f, 1.0f };

/// <summary>Color of the circle denoting the ship's point of rotation</summary>
static const ALLEGRO_COLOR G_COLOR_SHIP_CIRCLE = { 1.0f, 0.4f, 0.2f, 1.0f };

/// <summary>Radius of the circle drawn with respect to ship size</summary>
static const float G_SHIP_CIRCLE_RADIUS = { 0.08f };

int32_t g_texture_generate_ship_texture(ALLEGRO_BITMAP** bitmap)
{
	if (!bitmap)
	{
		return -1;
	}

	s_log_print("Generating ship bitmap - ");

	*bitmap = al_create_bitmap((int32_t)G_SHIP_SIZE.m_x, (int32_t)G_SHIP_SIZE.m_y);

	if (!*bitmap)
	{
		s_log_println("failed!");
		return -1;
	}

	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	al_set_target_bitmap(*bitmap);

	float x = 0.0f;
	float y = 0.0f;
	float w = G_SHIP_SIZE.m_x;
	float h = G_SHIP_SIZE.m_y;
	float cx = G_SHIP_CENTER_POINT.m_x * w;
	float cy = G_SHIP_CENTER_POINT.m_y * h;

	al_clear_to_color(S_COLOR_MAGIC_PINK.m_al_color);
	al_draw_filled_triangle(x + cx, y + 0.0f, x + 0.0f, y + cy, x + cx, y + h - 1.0f, G_COLOR_SHIP_HULL);
	al_draw_filled_triangle(x + cx, y + 0.0f, x + w - 1.0f, y + cy, x + cx, y + h - 1.0f, G_COLOR_SHIP_HULL);

	al_draw_line(x + cx, y + 0.0f, x + cx, y + h - 1.0f, G_COLOR_SHIP_CENTER_LINE, 2.0f);

	al_draw_line(x + cx, y + 0.0f, x + 0.0f, y + cy, G_COLOR_SHIP_OUTLINE, 2.0f);
	al_draw_line(x + cx, y + 0.0f, x + w - 1.0f, y + cy, G_COLOR_SHIP_OUTLINE, 2.0f);
	al_draw_line(x + cx, y + h - 1.0f, x + 0.0f, y + cy, G_COLOR_SHIP_OUTLINE, 2.0f);
	al_draw_line(x + cx, y + h - 1.0f, x + w - 1.0f, y + cy, G_COLOR_SHIP_OUTLINE, 2.0f);
	al_draw_filled_circle(x + cx, y + cy, x + G_SHIP_CIRCLE_RADIUS * w, G_COLOR_SHIP_CIRCLE);

	al_convert_mask_to_alpha(*bitmap, S_COLOR_MAGIC_PINK.m_al_color);

	al_set_target_bitmap(target);

	s_log_println("passed!");

	return 0;
}
