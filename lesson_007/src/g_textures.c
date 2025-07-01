#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"

int32_t g_texture_generate_ship_texture(ALLEGRO_BITMAP** bitmap);

void g_texture_set_zero(g_texture_list_t* textures)
{
	if (!textures)
	{
		return;
	}

	textures->m_ship_texture = NULL;
}

int32_t g_texture(g_texture_list_t* textures)
{
	if (g_texture_generate_ship_texture(&textures->m_ship_texture) < 0)
	{
		return -1;
	}

	return 0;
}

void g_texture_unitialize_data(g_texture_list_t* textures)
{
	if (textures->m_ship_texture)
	{
		al_destroy_bitmap(textures->m_ship_texture);
		textures->m_ship_texture = NULL;
	}
}
