#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_triangle.h"
#include "libspace/s_model.h"
#include "libspace/s_math.h"

extern ALLEGRO_VERTEX_DECL* s_vertex_decl;

static void s_model_index_buffer_zero_initialize_data(s_index_buffer_t* buffer)
{
	if (!buffer)
	{
		return;
	}

	buffer->m_count = 0;
	buffer->m_buffer = NULL;
}

static void s_model_vertex_buffer_zero_initialize_data(s_vertex_buffer_t* buffer)
{
	if (!buffer)
	{
		return;
	}

	buffer->m_count = 0;
	buffer->m_buffer = NULL;
}

void s_model_zero_initialize_data(s_model_t* model)
{
	if (!model)
	{
		return;
	}

	model->m_texture = NULL;
	s_model_index_buffer_zero_initialize_data(&model->m_index_buffer);
	s_model_vertex_buffer_zero_initialize_data(&model->m_vertex_buffer);
	s_point_set_zero(&model->m_center);
}

void s_model_initialize(s_model_t* model, int32_t* index_array, int32_t index_array_size, s_vertex_t* vertex_array, int32_t vertex_array_size, int32_t* outline_index_array, int32_t outline_index_array_size)
{
	if (!model)
	{
		return;
	}

	if (!index_array)
	{
		return;
	}

	if (!outline_index_array)
	{
		return;
	}

	if (!vertex_array)
	{
		return;
	}

	model->m_index_buffer.m_count = index_array_size;
	model->m_index_buffer.m_buffer = index_array;
	model->m_vertex_buffer.m_count = vertex_array_size;
	model->m_vertex_buffer.m_buffer = vertex_array;
	model->m_outline_buffer.m_count = outline_index_array_size;
	model->m_outline_buffer.m_buffer = outline_index_array;
}

void s_model_center_to_origin(s_model_t* model)
{
	if (!model)
	{
		return;
	}

	s_model_translate_f(model, -model->m_center.m_x, -model->m_center.m_y);
	s_point_set_zero(&model->m_center);
}

void s_model_center_to_point(s_model_t* model, const s_point_t* center)
{
	if (!model)
	{
		return;
	}

	if (!center)
	{
		return;
	}

	s_model_translate_f(model, model->m_center.m_x - center->m_x, model->m_center.m_y - center->m_y);
	s_point_add(&model->m_center, center);
}

void s_model_center_to_point_f(s_model_t* model, float x, float y)
{
	if (!model)
	{
		return;
	}

	s_model_translate_f(model, model->m_center.m_x - x, model->m_center.m_y - y);
	s_point_add_f(&model->m_center, x, y);
}

void s_model_translate(s_model_t* model, const s_point_t* delta)
{
	if (!model)
	{
		return;
	}

	if (!model->m_vertex_buffer.m_buffer)
	{
		return;
	}

	if (!delta)
	{
		return;
	}

	for (size_t i = 0; i < model->m_vertex_buffer.m_count; ++i)
	{
		s_point_add(&(model->m_vertex_buffer.m_buffer + i)->m_point, delta);
	}
	s_point_add(&model->m_center, delta);
}

void s_model_translate_f(s_model_t* model, float x, float y)
{
	if (!model)
	{
		return;
	}

	if (!model->m_vertex_buffer.m_buffer)
	{
		return;
	}

	for (size_t i = 0; i < model->m_vertex_buffer.m_count; ++i)
	{
		s_point_add_f(&(model->m_vertex_buffer.m_buffer + i)->m_point, x, y);
	}
	s_point_add_f(&model->m_center, x, y);
}

void s_model_rotate(s_model_t* model, float angle)
{
	static s_point_t* point = NULL;

	if (!model)
	{
		return;
	}

	if (!model->m_vertex_buffer.m_buffer)
	{
		return;
	}

	for (size_t i = 0; i < model->m_vertex_buffer.m_count; ++i)
	{
		point = &(model->m_vertex_buffer.m_buffer + i)->m_point;

		s_point_subtract(point, &model->m_center);
		s_point_rotate(point, angle);
		s_point_add(point, &model->m_center);
	}
}

void s_model_scale(s_model_t* model, float scale)
{
	if (!model)
	{
		return;
	}

	if (!model->m_vertex_buffer.m_buffer)
	{
		return;
	}

	for (size_t i = 0; i < model->m_vertex_buffer.m_count; ++i)
	{
		s_point_subtract(&(model->m_vertex_buffer.m_buffer + i)->m_point, &model->m_center);
		s_point_multiply_f(&(model->m_vertex_buffer.m_buffer + i)->m_point, scale);
		s_point_add(&(model->m_vertex_buffer.m_buffer + i)->m_point, &model->m_center);
	}
}

void s_model_draw(const s_model_t* model, int32_t flag)
{
	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;
	static ALLEGRO_BITMAP* texture = NULL;
	static int32_t draw_flag = ALLEGRO_PRIM_LINE_LOOP;
	static const s_index_buffer_t* buffer = NULL;

	if (!model)
	{
		return;
	}

	if (!model->m_index_buffer.m_buffer)
	{
		return;
	}

	if (!model->m_vertex_buffer.m_buffer)
	{
		return;
	}

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	switch (flag)
	{
	case S_MODEL_DRAW_FLAG_TEXTURED:
	{
		texture = model->m_texture;
		buffer = &model->m_index_buffer;
		draw_flag = ALLEGRO_PRIM_TRIANGLE_LIST;
	} break;
	case S_MODEL_DRAW_FLAG_OUTLINE:
	{
		texture = NULL;
		buffer = &model->m_outline_buffer;
		draw_flag = ALLEGRO_PRIM_LINE_LOOP;
	} break;
	case S_MODEL_DRAW_FLAG_WIREFRAME:
	{
		texture = NULL;
		buffer = &model->m_index_buffer;
		draw_flag = ALLEGRO_PRIM_LINE_LOOP;
	} break;
	case S_MODEL_DRAW_FLAG_FULLFRAME:
	{
		texture = NULL;
		buffer = &model->m_index_buffer;
		draw_flag = ALLEGRO_PRIM_TRIANGLE_LIST;
	} break;
	default:
	{
		texture = NULL;
		buffer = NULL;
		draw_flag = -1;
	} break;
	};

	if (!buffer)
	{
		return;
	}

	al_draw_indexed_prim(model->m_vertex_buffer.m_buffer,
		s_vertex_decl,
		texture,
		buffer->m_buffer,
		buffer->m_count,
		draw_flag);

	al_use_transform(&backup);
}

void s_models_generate_quad_model_vertices(s_quad_model_t* model, const s_point_t* size, const s_point_t* uv, const s_point_t* uv_size, const s_color_t* color)
{
	if (!model)
	{
		return;
	}

	int32_t indices[S_TRIANGLE_POINT_COUNT * S_QUAD_TRIANGLE_COUNT] =
	{
		0, 2, 1, 0, 3, 2
	};

	s_point_t vertices[S_QUAD_VERTEX_COUNT] =
	{
		{ 0.0f, 0.0f},
		{ 0.0f, 1.0f},
		{ 1.0f, 1.0f},
		{ 1.0f, 0.0f}
	};

	int32_t outline[S_QUAD_OUTLINE_VERTEX_COUNT] =
	{
		0, 1, 2, 3
	};

	s_point_t _size =
	{
		1.0f, 1.0f
	};

	s_point_t center =
	{
		0.5f, 0.5f
	};

	s_point_t _uv =
	{
		0.0f, 0.0f
	};

	s_point_t _uv_size =
	{
		1.0f, 1.0f
	};
	s_color_t _color =
	{
		1.0f,
		1.0f,
		1.0f,
		1.0f
	};

	if (size)
	{
		for (int32_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
		{
			_size.m_float_array[i] = size->m_float_array[i];
		}
	}

	if (uv)
	{
		for (int32_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
		{
			_uv.m_float_array[i] = uv->m_float_array[i];
		}
	}

	if (uv_size)
	{
		for (int32_t i = 0; i < S_POINT_FLOAT_SIZE; ++i)
		{
			_uv_size.m_float_array[i] = uv_size->m_float_array[i];
		}
	}

	if (color)
	{
		for (int32_t i = 0; i < S_COLOR_FLOAT_SIZE; ++i)
		{
			_color.m_float_array[i] = color->m_float_array[i];
		}
	}

	for (int32_t i = 0; i < S_TRIANGLE_POINT_COUNT * S_QUAD_TRIANGLE_COUNT; ++i)
	{
		model->m_indices[i] = indices[i];
	}

	for (int32_t v_index = 0; v_index < S_QUAD_VERTEX_COUNT; ++v_index)
	{
		s_point_set(&model->m_vertices[v_index].m_point, &vertices[v_index]);
		s_point_subtract(&model->m_vertices[v_index].m_point, &center);
		//s_point_rotate(&model->m_vertices[v_index].m_point, S_PI_HALF);
		model->m_vertices[v_index].m_point.m_x *= _size.m_x;
		model->m_vertices[v_index].m_point.m_y *= _size.m_y;

		model->m_vertices[v_index].m_uv.m_x = _uv.m_x + (_uv_size.m_x * vertices[v_index].m_x);
		model->m_vertices[v_index].m_uv.m_y = _uv.m_y + (_uv_size.m_y * vertices[v_index].m_y);

		for (int32_t i = 0; i < S_COLOR_FLOAT_SIZE; ++i)
		{
			model->m_vertices[v_index].m_color.m_float_array[i] = _color.m_float_array[i];
		}
	}

	for (int32_t o = 0; o < S_QUAD_OUTLINE_VERTEX_COUNT; ++o)
	{
		model->m_outline[o] = outline[o];
	}
}

void s_model_validate_screen(s_model_t* model, const s_point_t* top_left, const s_point_t* bottom_right)
{
	s_point_t point = { 0.0f, 0.0f };

	if (!model)
	{
		return;
	}

	if (!top_left)
	{
		return;
	}

	if (!bottom_right)
	{
		return;
	}

	if (model->m_center.m_x < top_left->m_x)
	{
		point.m_x = (bottom_right->m_x - top_left->m_x) + 1.0f;
	}
	else
	{
		if (model->m_center.m_x > bottom_right->m_x)
		{
			point.m_x = -(bottom_right->m_x - top_left->m_x) - 1.0f;
		}
	}

	if (model->m_center.m_y < top_left->m_y)
	{
		point.m_y = (bottom_right->m_y - top_left->m_y) + 1.0f;
	}
	else
	{
		if (model->m_center.m_y > bottom_right->m_y)
		{
			point.m_y = -(bottom_right->m_y - top_left->m_y) - 1.0f;
		}
	}

	s_model_translate(model, &point);
}
