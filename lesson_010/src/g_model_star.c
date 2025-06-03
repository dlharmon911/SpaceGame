#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_models.h"
#include "g_textures.h"

static const float G_STAR_MODEL_SCALE = 1.5f;
static const float G_STAR_COLOR_SCALE = 1.75f;

void g_model_generate_star_model(s_quad_model_t* star_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale)
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

	s_point_t size = { G_TEXTURE_STAR_CHUNK_SIZE.m_x * scale, G_TEXTURE_STAR_CHUNK_SIZE.m_y * scale };
	s_point_t uv_size = { G_TEXTURE_STAR_CHUNK_SIZE.m_x, G_TEXTURE_STAR_CHUNK_SIZE.m_y };

	uint32_t t_u = (uint32_t)(G_TEXTURE_STAR_SIZE.m_x / G_TEXTURE_STAR_CHUNK_SIZE.m_x);
	uint32_t t_v = (uint32_t)(G_TEXTURE_STAR_SIZE.m_y / G_TEXTURE_STAR_CHUNK_SIZE.m_y);
	s_point_t uv =
	{
		(float)s_random_generate(t_u - 1),
		(float)s_random_generate(t_v - 1)
	};
	float color_scale = s_math_min_f(1.0f, scale * G_STAR_COLOR_SCALE);
	s_color_t color = { color_scale, color_scale, color_scale, color_scale };

	s_models_generate_quad_model_vertices(star_model, &size, &uv, &uv_size, &color);

	model->m_index_buffer.m_count = S_QUAD_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT;
	model->m_index_buffer.m_buffer = star_model->m_indices;
	model->m_vertex_buffer.m_count = S_QUAD_VERTEX_COUNT;
	model->m_vertex_buffer.m_buffer = star_model->m_vertices;
	model->m_outline_buffer.m_count = S_QUAD_OUTLINE_VERTEX_COUNT;
	model->m_outline_buffer.m_buffer = star_model->m_outline;

	s_point_set_zero(&model->m_center);
	s_model_scale(model, scale * G_STAR_MODEL_SCALE);
}
