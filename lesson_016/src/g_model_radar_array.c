#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_model_data.h"
#include "g_texture_data.h"

void g_model_generate_radar_model_quad(s_quad_model_t* quad_model, s_model_t* model, const s_point_t* position, const s_point_t* size, float scale)
{
	s_point_t uv_pos = { 0.0f, 0.0f };
	s_point_t uv_size = { 0.0f, 0.0f };
	s_color_t color = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (!quad_model)
	{
		return;
	}

	if (!position)
	{
		return;
	}

	if (!size)
	{
		return;
	}

	s_point_set(&uv_pos, position);
	s_point_set(&uv_size, size);

	s_models_generate_quad_model_vertices(quad_model, size, &uv_pos, &uv_size, &color);

	s_model_initialize(model,
		quad_model->m_indices,
		S_QUAD_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT,
		quad_model->m_vertices,
		S_QUAD_VERTEX_COUNT,
		quad_model->m_outline,
		S_QUAD_OUTLINE_VERTEX_COUNT);

	s_point_set_zero(&model->m_center);
	s_model_scale(model, scale);
}

void g_model_generate_radar_model_array(s_quad_model_t* quad_model_array, s_model_t* model_array, ALLEGRO_BITMAP* texture)
{
	if (!quad_model_array)
	{
		return;
	}

	if (!model_array)
	{
		return;
	}

	if (!texture)
	{
		return;
	}

	s_point_t position[G_MODEL_RADAR_MODEL_COUNT] =
	{
		{ 0.0f, 0.0f},
		{ 128.0f, 0.0f},
		{ 0.0f, 128.0f},
		{ 128.0f, 128.0f}
	};

	s_point_t size[G_MODEL_RADAR_MODEL_COUNT] =
	{
		{ 128.0f, 128.0f},
		{ 128.0f, 128.0f},
		{ 128.0f, 128.0f},
		{ 16.0f, 16.0f}
	};

	float scale[G_MODEL_RADAR_MODEL_COUNT] =
	{
		1.0f,
		1.0f,
		1.0f,
		1.0f
	};

	for (size_t i = 0; i < G_MODEL_RADAR_MODEL_COUNT; ++i)
	{
		model_array[i].m_texture = texture;
		g_model_generate_radar_model_quad(&quad_model_array[i], &model_array[i], &position[i], &size[i], scale[i]);
	}
}
