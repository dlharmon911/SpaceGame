#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_models.h"

static void g_models_generate_ship_model_vertices(g_ship_model_t* model, const s_point_t* center, float w, float h)
{
	int32_t indices[S_TRIANGLE_POINT_COUNT * G_SHIP_TRIANGLE_COUNT] =
	{
		0, 2, 1, 0, 3, 2
	};

	s_point_t vertices[G_SHIP_VERTEX_COUNT] =
	{
		{center->m_x, 0.0f},
		{0.0f, center->m_y},
		{center->m_x, h - 1.0f},
		{w - 1.0f, center->m_y}
	};

	int32_t outline[G_SHIP_OUTLINE_VERTEX_COUNT] =
	{
		0, 1, 2, 3
	};

	for (int32_t i = 0; i < S_TRIANGLE_POINT_COUNT * G_SHIP_TRIANGLE_COUNT; ++i)
	{
		model->m_indices[i] = indices[i];
	}

	for (int32_t v_index = 0; v_index < G_SHIP_VERTEX_COUNT; ++v_index)
	{
		s_point_set(&model->m_vertices[v_index].m_point, &vertices[v_index]);
		s_point_subtract(&model->m_vertices[v_index].m_point, center);

		model->m_vertices[v_index].m_uv.m_x = vertices[v_index].m_x;
		model->m_vertices[v_index].m_uv.m_y = vertices[v_index].m_y;

		model->m_vertices[v_index].m_color.m_red =
			model->m_vertices[v_index].m_color.m_green =
			model->m_vertices[v_index].m_color.m_blue =
			model->m_vertices[v_index].m_color.m_alpha = 1.0f;
	}

	for (int32_t o = 0; o < G_SHIP_OUTLINE_VERTEX_COUNT; ++o)
	{
		model->m_outline[o] = outline[o];
	}
}

void g_model_generate_ship_model(g_ship_model_t* ship_model, s_model_t* model, ALLEGRO_BITMAP* texture)
{
	if (!ship_model)
	{
		return;
	}

	if (!model)
	{
		return;
	}

	model->m_texture = texture;

	float w = G_SHIP_SIZE.m_x;
	float h = G_SHIP_SIZE.m_y;
	s_point_t center = { G_SHIP_CENTER_POINT.m_x * w, G_SHIP_CENTER_POINT.m_y * h };

	g_models_generate_ship_model_vertices(ship_model, &center, w, h);

	s_model_initialize(model,
		ship_model->m_indices,
		G_SHIP_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT,
		ship_model->m_vertices,
		G_SHIP_VERTEX_COUNT,
		ship_model->m_outline,
		G_SHIP_OUTLINE_VERTEX_COUNT);

	s_point_set_zero(&model->m_center);
	s_model_rotate(model, S_PI_HALF);
	s_model_scale(model, G_SHIP_SIZE_SCALE);
}
