#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_vertex.h"

ALLEGRO_VERTEX_DECL* s_vertex_decl = NULL;

void s_vertex_create_decl()
{
	ALLEGRO_VERTEX_ELEMENT elements[] =
	{
		{ ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_2, offsetof(s_vertex_t, m_point)},
		{ ALLEGRO_PRIM_TEX_COORD_PIXEL, ALLEGRO_PRIM_FLOAT_2, offsetof(s_vertex_t, m_uv)},
		{ ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(s_vertex_t, m_color)},
	  {0, 0, 0}
	};

	if (s_vertex_decl)
	{
		return;
	}

	s_vertex_decl = al_create_vertex_decl(elements, sizeof(s_vertex_t));
}

bool s_vertex_decl_created()
{
	return (s_vertex_decl != NULL);
}

void s_vertex_destroy_decl()
{
	if (s_vertex_decl)
	{
		al_destroy_vertex_decl(s_vertex_decl);
		s_vertex_decl = NULL;
	}
}
