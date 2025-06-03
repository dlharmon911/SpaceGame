#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_models.h"
#include "g_textures.h"
#include "g_bullet.h"

void g_model_generate_bullet_model(s_quad_model_t* quad_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale)
{
	if (!quad_model)
	{
		return;
	}

	if (!model)
	{
		return;
	}

	model->m_texture = texture;

	s_point_t size = { G_BULLET_SIZE.m_x * scale, G_BULLET_SIZE.m_y * scale };

	s_models_generate_quad_model_vertices(quad_model, &size, &G_BULLET_TEXTURE_UV, &G_BULLET_TEXTURE_UV_SIZE, NULL);

	model->m_index_buffer.m_count = S_QUAD_TRIANGLE_COUNT * S_TRIANGLE_POINT_COUNT;
	model->m_index_buffer.m_buffer = quad_model->m_indices;
	model->m_vertex_buffer.m_count = S_QUAD_VERTEX_COUNT;
	model->m_vertex_buffer.m_buffer = quad_model->m_vertices;
	model->m_outline_buffer.m_count = S_QUAD_OUTLINE_VERTEX_COUNT;
	model->m_outline_buffer.m_buffer = quad_model->m_outline;
	s_model_translate_f(model, 0.0f, 1.5f);
	s_point_set_zero(&model->m_center);
}
