#ifndef _HEADER_GUARD_LIBSPACE_VERTEX_H_
#define _HEADER_GUARD_LIBSPACE_VERTEX_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_color.h"

enum
{
	S_VERTEX_FLOAT_SIZE = 2 * S_POINT_FLOAT_SIZE + S_COLOR_FLOAT_SIZE
};

typedef struct s_vertex_t
{
	union
	{
		struct
		{
			s_point_t m_point;
			s_point_t m_uv;
			s_color_t m_color;
		};
		float m_float_array[S_VERTEX_FLOAT_SIZE];
	};
} s_vertex_t;

void s_vertex_set_zero(s_vertex_t* vertex);
const ALLEGRO_VERTEX_DECL* s_vertex_get_decl();
void s_vertex_create_decl();
bool s_vertex_decl_created();
void s_vertex_destroy_decl();

#endif // !_HEADER_GUARD_LIBSPACE_VERTEX_H_
