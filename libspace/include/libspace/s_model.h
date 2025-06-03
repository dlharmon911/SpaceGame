#ifndef _HEADER_GUARD_LIBSPACE_MODEL_H_
#define _HEADER_GUARD_LIBSPACE_MODEL_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_vertex.h"
#include "libspace/s_color.h"
#include "libspace/s_triangle.h"

enum
{
	S_MODEL_DRAW_FLAG_TEXTURED,
	S_MODEL_DRAW_FLAG_OUTLINE,
	S_MODEL_DRAW_FLAG_WIREFRAME,
	S_MODEL_DRAW_FLAG_FULLFRAME,
	S_MODEL_DRAW_FLAG_COUNT
};

enum
{
	S_QUAD_VERTEX_COUNT = 4,
	S_QUAD_OUTLINE_VERTEX_COUNT = 4,
	S_QUAD_TRIANGLE_COUNT = 2
};

typedef struct s_index_buffer_t
{
	int32_t m_count;
	int32_t* m_buffer;
} s_index_buffer_t;

typedef struct s_vertex_buffer_t
{
	int32_t m_count;
	s_vertex_t* m_buffer;
} s_vertex_buffer_t;

typedef struct s_model_t
{
	ALLEGRO_BITMAP* m_texture;
	s_index_buffer_t m_index_buffer;
	s_vertex_buffer_t m_vertex_buffer;
	s_index_buffer_t m_outline_buffer;
	s_point_t m_center;
} s_model_t;

typedef struct s_quad_model_t
{
	int32_t m_indices[S_TRIANGLE_POINT_COUNT * S_QUAD_TRIANGLE_COUNT];
	s_vertex_t m_vertices[S_QUAD_VERTEX_COUNT];
	int32_t m_outline[S_QUAD_OUTLINE_VERTEX_COUNT];
} s_quad_model_t;

void s_models_generate_quad_model_vertices(s_quad_model_t* model, const s_point_t* size, const s_point_t* uv, const s_point_t* uv_size, const s_color_t* color);
void s_model_zero_initialize_data(s_model_t* model);
void s_model_initialize(s_model_t* model, int32_t* index_array, int32_t index_array_size, s_vertex_t* vertex_array, int32_t vertex_array_size, int32_t* outline_index_array, int32_t outline_index_array_size);
void s_model_center_to_origin(s_model_t* model);
void s_model_center_to_point(s_model_t* model, const s_point_t* center);
void s_model_center_to_point_f(s_model_t* model, float x, float y);
void s_model_translate(s_model_t* model, const s_point_t* delta);
void s_model_translate_f(s_model_t* model, float x, float y);
void s_model_rotate(s_model_t* model, float angle);
void s_model_scale(s_model_t* model, float scale);
void s_model_draw(const s_model_t* model, int32_t flag);
void s_model_validate_screen(s_model_t* model, const s_point_t* top_left, const s_point_t* bottom_right);

#endif // !_HEADER_GUARD_LIBSPACE_MODEL_H_
