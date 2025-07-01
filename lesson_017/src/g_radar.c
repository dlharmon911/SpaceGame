#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"
#include "g_radar.h"

void g_radar_set_zero(g_radar_t* radar)
{
	if (!radar)
	{
		return;
	}

	for (size_t i = 0; i < G_MODEL_RADAR_MODEL_COUNT; ++i)
	{
		s_model_set_zero(&radar->m_model[i]);
	}
	s_point_set_zero(&radar->m_position);
	radar->m_angle = 0.0f;
}

void g_radar_initialize(ALLEGRO_BITMAP* texture, g_radar_t* radar)
{
	if (!texture)
	{
		return;
	}

	if (!radar)
	{
		return;
	}

	g_model_generate_radar_model_array(radar->m_quad_model, radar->m_model, texture);
	s_point_set_f(&radar->m_position, G_RADAR_MARGIN.m_x + G_RADAR_SIZE_HALF.m_x, G_RADAR_MARGIN.m_y + G_RADAR_SIZE_HALF.m_y);

	radar->m_boulder_array = NULL;
	radar->m_ship_center = NULL;
	radar->m_angle = 0.0f;
}

static void g_radar_draw_boulder_array_icons(const g_radar_t* radar, int32_t flag)
{
	static ALLEGRO_TRANSFORM backup = { 0 };
	static ALLEGRO_TRANSFORM transform = { 0 };
	s_point_t difference = { 0.0f, 0.0f };
	float length = 0.0f;
	float angle = 0.0f;
	const g_boulder_t* boulder = NULL;
	const g_boulder_node_t* boulder_node = NULL;
	float scale = 0.0f;
	float diff = 0.0f;
	int32_t index = 0;

	al_copy_transform(&backup, al_get_current_transform());

	for (size_t i = 0; i < radar->m_boulder_array->m_max_count; ++i)
	{
		boulder_node = &radar->m_boulder_array->m_boulder[i];

		if (s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_INITIALIZED) &&
			s_flags_is_set(boulder_node->m_status, G_BOULDER_STATUS_LIVE))
		{
			boulder = &boulder_node->m_boulder;

			s_point_get_difference(&difference, radar->m_ship_center, &boulder->m_object.m_model.m_center);
			angle = atan2f(difference.m_y, difference.m_x);

			float b = -radar->m_angle + S_PI_HALF;
			float a = angle;

			diff = a - b;
			while (diff < 0.0f)
			{
				diff += S_PI_DOUBLE;
			}
			while (diff >= S_PI_DOUBLE)
			{
				diff -= S_PI_DOUBLE;
			}

			index = (((int32_t)s_math_radian_to_degree(diff) * G_MODEL_RADAR_MODEL_ICON_COUNT) / (int32_t)S_PI_DEG_DOUBLE) + G_MODEL_RADAR_MODEL_ICON_START;

			if (index < G_MODEL_RADAR_MODEL_ICON_START || index > G_MODEL_RADAR_MODEL_ICON_END)
			{
				continue;
			}

			length = s_point_get_length(&difference);

			if (length >= (G_RADAR_LENGTH_MAX - G_RADAR_LENGTH_EDGE_MARGIN))
			{
				continue;
			}

			scale = (length / G_RADAR_LENGTH_MAX);

			difference.m_x = -G_RADAR_SIZE_HALF.m_x * scale * cosf(angle);
			difference.m_y = G_RADAR_SIZE_HALF.m_y * scale * sinf(angle);

			al_identity_transform(&transform);
			s_point_translate(&transform, &difference);
			al_compose_transform(&transform, &backup);
			al_use_transform(&transform);



			const s_model_t* model = &radar->m_model[index];

			if (!model)
			{
				continue;
			}

			s_model_draw(model, flag);
		}
	}

	al_use_transform(&backup);
}

void g_radar_draw(const g_radar_t* radar, float north, int32_t flag)
{
	static ALLEGRO_TRANSFORM backup = { 0 };
	static ALLEGRO_TRANSFORM transform = { 0 };

	if (!radar)
	{
		return;
	}
	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_rotate_transform(&transform, north);
	s_point_translate(&transform, &radar->m_position);
	al_scale_transform(&transform, G_RADAR_SCALE, -G_RADAR_SCALE);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	s_model_draw(&radar->m_model[G_MODEL_RADAR_MODEL_BACKGROUND], flag);
	s_model_draw(&radar->m_model[G_MODEL_RADAR_MODEL_SWEEP], flag);
	s_model_draw(&radar->m_model[G_MODEL_RADAR_MODEL_CIRCLE], flag);


	al_identity_transform(&transform);
	al_rotate_transform(&transform, north);
	s_point_translate(&transform, &radar->m_position);
	al_scale_transform(&transform, G_RADAR_SCALE, -G_RADAR_SCALE);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	g_radar_draw_boulder_array_icons(radar, flag);

	al_identity_transform(&transform);
	s_point_translate(&transform, &radar->m_position);
	al_scale_transform(&transform, G_RADAR_SCALE, -G_RADAR_SCALE);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	al_draw_textf(radar->m_font, al_map_rgb_f(1.0f, 1.0f, 1.0f), 0.0f, radar->m_position.m_y, ALLEGRO_ALIGN_CENTER, "(%d, %d)", (int32_t)radar->m_ship_center->m_x, (int32_t)radar->m_ship_center->m_y);
	al_use_transform(&backup);
}

void g_radar_update(g_radar_t* radar)
{
	if (!radar)
	{
		return;
	}

	radar->m_angle += G_RADAR_ROTATION_AMOUNT;
	if (radar->m_angle > S_PI_DOUBLE)
	{
		radar->m_angle -= S_PI_DOUBLE;
	}
	s_model_rotate(&radar->m_model[G_MODEL_RADAR_MODEL_SWEEP], G_RADAR_ROTATION_AMOUNT);
}
