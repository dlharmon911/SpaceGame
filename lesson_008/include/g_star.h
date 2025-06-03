#ifndef _HEADER_GUARD_STAR_H_
#define _HEADER_GUARD_STAR_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

typedef struct g_star_t
{
	s_object_t m_object;
	g_star_model_t m_star_model;
	float m_z;
} g_star_t;

void g_star_zero_initialize_data(g_star_t* star);
void g_star_initialize(const g_texture_list_t* texture_list, g_star_t* star, float z);
void g_star_draw(const g_star_t* star, int32_t flag);
void g_star_update(g_star_t* star, const s_point_t* velocity);

#endif // !_HEADER_GUARD_SHIP_H_
