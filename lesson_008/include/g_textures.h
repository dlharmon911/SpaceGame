#ifndef _HEADER_GUARD_TEXTURES_H_
#define _HEADER_GUARD_TEXTURES_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

/// <summary>Size of the bitmap for the ship</summary>
static const s_point_t G_TEXTURE_SHIP_SIZE = { 64.0f, 64.0f };

/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_STAR_SIZE = { 256.0f, 256.0f };

typedef struct g_texture_list_t
{
	ALLEGRO_BITMAP* m_ship;
	ALLEGRO_BITMAP* m_star;
} g_texture_list_t;

void g_texture_set_zero(g_texture_list_t* textures);
int32_t g_texture(g_texture_list_t* textures);
void g_texture_unitialize_data(g_texture_list_t* textures);

#endif // !_HEADER_GUARD_TEXTURES_H_
