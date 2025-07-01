#ifndef _HEADER_GUARD_TEXTURES_H_
#define _HEADER_GUARD_TEXTURES_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

typedef struct g_texture_list_t
{
	ALLEGRO_BITMAP* m_ship_texture;
} g_texture_list_t;

void g_texture_set_zero(g_texture_list_t* textures);
int32_t g_texture(g_texture_list_t* textures);
void g_texture_unitialize_data(g_texture_list_t* textures);

#endif // !_HEADER_GUARD_TEXTURES_H_
