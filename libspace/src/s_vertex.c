#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_vertex.h"

static ALLEGRO_VERTEX_DECL** s_vertex_get_internal_decl()
{
	static ALLEGRO_VERTEX_DECL* s_vertex_decl = NULL;

	return &s_vertex_decl;
}

void s_vertex_zero_initialize_data(s_vertex_t* vertex)
{
	if (!vertex)
	{
		return;
	}

	for (size_t i = 0; i < S_VERTEX_FLOAT_SIZE; ++i)
	{
		vertex->m_float_array[i] = 0.0f;
	}
}

const ALLEGRO_VERTEX_DECL* s_vertex_get_decl()
{
	const ALLEGRO_VERTEX_DECL** vertex_decl = s_vertex_get_internal_decl();

	if (!vertex_decl)
	{
		return NULL;
	}

	return *vertex_decl;
}

void s_vertex_create_decl()
{
	ALLEGRO_VERTEX_ELEMENT elements[] =
	{
		{ ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_2, offsetof(s_vertex_t, m_point)},
		{ ALLEGRO_PRIM_TEX_COORD_PIXEL, ALLEGRO_PRIM_FLOAT_2, offsetof(s_vertex_t, m_uv)},
		{ ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(s_vertex_t, m_color)},
		{0, 0, 0}
	};
	ALLEGRO_VERTEX_DECL** vertex_decl = s_vertex_get_internal_decl();

	if (!vertex_decl)
	{
		return;
	}

	if (*vertex_decl)
	{
		return;
	}

	(*vertex_decl) = al_create_vertex_decl(elements, sizeof(s_vertex_t));
}

bool s_vertex_decl_created()
{
	ALLEGRO_VERTEX_DECL** vertex_decl = s_vertex_get_internal_decl();

	return (vertex_decl && *vertex_decl);
}

void s_vertex_destroy_decl()
{
	ALLEGRO_VERTEX_DECL** vertex_decl = s_vertex_get_internal_decl();

	if (vertex_decl && *vertex_decl)
	{
		al_destroy_vertex_decl(*vertex_decl);
		*vertex_decl = NULL;
	}
}
