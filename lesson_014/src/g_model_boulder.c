#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_models.h"
#include "g_textures.h"

static const float G_BOULDER_SIZE = 128.0f;
static const float G_BOULDER_RADIUS_DIFFERANCE_MAX = 12.0f;
static const float G_BOULDER_RADIUS_PERMUTATION_MAX = 0.45f;
static const float G_BOULDER_RADIUS_PERMUTATION_MIN = 0.15f;

static float g_bitmaps_permutate_radius(float radius, float min_radius, float max_radius)
{
	int r = s_random_generate(99);

	if (r < 50)
	{
		float new_radius = s_random_generate_constraint_f(min_radius, max_radius);

		if (fabsf(radius - new_radius) >= G_BOULDER_RADIUS_DIFFERANCE_MAX)
		{
			new_radius = ((radius + new_radius) * 0.5f);
		}

		return new_radius;
	}

	return radius;
}

static void g_models_generate_boulder_model_scaled(g_boulder_model_t* model, float scale, float* max_radius)
{
	float w = G_BOULDER_SIZE;
	float radius = 0.0f;
	float angle = 0.0f;
	float arc = (S_PI_DOUBLE / (float)(G_BOULDER_OUTLINE_VERTEX_COUNT - 1));

	if (!model)
	{
		return;
	}

	if (!max_radius)
	{
		return;
	}

	for (int32_t i = 0; i < G_BOULDER_TRIANGLE_COUNT; ++i)
	{
		model->m_indices[i * S_TRIANGLE_POINT_COUNT + 0] = 0;
		model->m_indices[i * S_TRIANGLE_POINT_COUNT + 1] = i + 1;
		model->m_indices[i * S_TRIANGLE_POINT_COUNT + 2] = i + 2;
	}
	model->m_indices[G_BOULDER_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT - 1] = 1;

	s_point_set_zero(&model->m_vertices[0].m_point);

	for (int32_t v = 1; v < G_BOULDER_VERTEX_COUNT; ++v)
	{
		radius = scale * g_bitmaps_permutate_radius(w * ((G_BOULDER_RADIUS_PERMUTATION_MAX + G_BOULDER_RADIUS_PERMUTATION_MIN) * 0.5f), w * G_BOULDER_RADIUS_PERMUTATION_MIN, w * G_BOULDER_RADIUS_PERMUTATION_MAX);

		(*max_radius) = s_math_max_f(*max_radius, radius);

		angle += arc;

		model->m_vertices[v].m_point.m_x = radius * cosf(angle);
		model->m_vertices[v].m_point.m_y = radius * sinf(angle);
	}

	s_point_t min_f = { 10000.0f, 10000.0f };
	s_point_t max_f = { -10000.0f, -10000.0f };

	for (int32_t v_index = 0; v_index < G_BOULDER_VERTEX_COUNT; ++v_index)
	{
		min_f.m_x = s_math_min_f(min_f.m_x, model->m_vertices[v_index].m_point.m_x);
		min_f.m_y = s_math_min_f(min_f.m_y, model->m_vertices[v_index].m_point.m_y);
		max_f.m_x = s_math_max_f(max_f.m_x, model->m_vertices[v_index].m_point.m_x);
		max_f.m_y = s_math_max_f(max_f.m_y, model->m_vertices[v_index].m_point.m_y);
	}

	// code to pick a random point on the texture as the top/left
	// give s a bit of variation
	s_point_t size = { max_f.m_x - min_f.m_x, max_f.m_y - min_f.m_y };
	s_point_t tex = { G_TEXTURE_BOULDER_SIZE.m_x - size.m_x, G_TEXTURE_BOULDER_SIZE.m_y - size.m_y };
	s_point_t tuv =
	{
		s_random_generate_f(tex.m_x),
		s_random_generate_f(tex.m_y)
	};

	for (int32_t v_index = 0; v_index < G_BOULDER_VERTEX_COUNT; ++v_index)
	{
		model->m_vertices[v_index].m_uv.m_x = tuv.m_x + model->m_vertices[v_index].m_point.m_x;
		model->m_vertices[v_index].m_uv.m_y = tuv.m_y + model->m_vertices[v_index].m_point.m_y;

		model->m_vertices[v_index].m_color.m_red =
			model->m_vertices[v_index].m_color.m_green =
			model->m_vertices[v_index].m_color.m_blue =
			model->m_vertices[v_index].m_color.m_alpha = 1.0f;
	}

	for (int32_t o = 0; o < (G_BOULDER_OUTLINE_VERTEX_COUNT - 1); ++o)
	{
		model->m_outline[o] = o + 1;
	}
	model->m_outline[G_BOULDER_OUTLINE_VERTEX_COUNT - 1] = 1;
}

void g_model_generate_boulder_model(g_boulder_model_t* boulder_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale, float* radius)
{
	if (!boulder_model)
	{
		return;
	}

	if (!model)
	{
		return;
	}

	if (!radius)
	{
		return;
	}

	model->m_texture = texture;

	g_models_generate_boulder_model_scaled(boulder_model, scale, radius);

	s_model_initialize(model, 
		boulder_model->m_indices,
		G_BOULDER_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT,
		boulder_model->m_vertices,
		G_BOULDER_VERTEX_COUNT,
		boulder_model->m_outline,
		G_BOULDER_OUTLINE_VERTEX_COUNT);

}
