#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_model_data.h"
#include "g_texture_data.h"

static void g_models_generate_star_model_vertices(g_star_model_t* model, const s_point_t* center, float u, float v, float z)
{
	int32_t indices[S_TRIANGLE_POINT_COUNT * G_STAR_TRIANGLE_COUNT] =
	{
		0, 1, 2, 0, 2, 3
	};

	s_point_t vertices[G_STAR_VERTEX_COUNT] =
	{
		{ 0.0f, 0.0f},
		{ 0.0f, 1.0f},
		{ 1.0f, 1.0f},
		{ 1.0f, 0.0f}
	};

	int32_t outline[G_STAR_OUTLINE_VERTEX_COUNT] =
	{
		0, 1, 2, 3
	};

	for (int32_t i = 0; i < S_TRIANGLE_POINT_COUNT * G_STAR_TRIANGLE_COUNT; ++i)
	{
		model->m_indices[i] = indices[i];
	}

	for (int32_t v_index = 0; v_index < G_STAR_VERTEX_COUNT; ++v_index)
	{
		s_point_set(&model->m_vertices[v_index].m_point, &vertices[v_index]);
		s_point_subtract(&model->m_vertices[v_index].m_point, center);
		s_point_rotate(&model->m_vertices[v_index].m_point, S_PI_HALF);
		s_point_multiply_f(&model->m_vertices[v_index].m_point, G_TEXTURE_STAR_CHUNK_SIZE.m_x * 0.35f);

		model->m_vertices[v_index].m_uv.m_x = ((u + vertices[v_index].m_x) * G_TEXTURE_STAR_CHUNK_SIZE.m_x) - vertices[v_index].m_x;
		model->m_vertices[v_index].m_uv.m_y = ((v + vertices[v_index].m_y) * G_TEXTURE_STAR_CHUNK_SIZE.m_y) - vertices[v_index].m_y;

		model->m_vertices[v_index].m_color.m_red =
			model->m_vertices[v_index].m_color.m_green =
			model->m_vertices[v_index].m_color.m_blue =
			model->m_vertices[v_index].m_color.m_alpha = z;
	}

	for (int32_t o = 0; o < G_STAR_OUTLINE_VERTEX_COUNT; ++o)
	{
		model->m_outline[o] = outline[o];
	}
}

void g_model_generate_star_model(g_star_model_t* star_model, s_model_t* model, ALLEGRO_BITMAP* texture, float z)
{
	if (!star_model)
	{
		return;
	}

	if (!model)
	{
		return;
	}

	model->m_texture = texture;

	s_point_t center = { 0.5f, 0.5f };

	uint32_t t_u = (uint32_t)(G_TEXTURE_STAR_SIZE.m_x / G_TEXTURE_STAR_CHUNK_SIZE.m_x);
	uint32_t t_v = (uint32_t)(G_TEXTURE_STAR_SIZE.m_y / G_TEXTURE_STAR_CHUNK_SIZE.m_y);
	float u = (float)s_random_generate(t_u - 1);
	float v = (float)s_random_generate(t_v - 1);

	g_models_generate_star_model_vertices(star_model, &center, u, v, z);

	model->m_index_buffer.m_count = G_STAR_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT;
	model->m_index_buffer.m_buffer = star_model->m_indices;
	model->m_vertex_buffer.m_count = G_STAR_VERTEX_COUNT;
	model->m_vertex_buffer.m_buffer = star_model->m_vertices;
	model->m_outline_buffer.m_count = G_STAR_OUTLINE_VERTEX_COUNT;
	model->m_outline_buffer.m_buffer = star_model->m_outline;

	s_point_set_zero(&model->m_center);
	s_model_scale(model, z);
}
