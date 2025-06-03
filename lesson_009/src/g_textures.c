#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"

void g_texture_zero_initialize_data(g_texture_list_t* textures)
{
	if (!textures)
	{
		return;
	}

	textures->m_ship = NULL;
	textures->m_star = NULL;
	textures->m_boulder = NULL;
}

int32_t g_texture_initialize_data(g_texture_list_t* textures)
{
	if (g_texture_generate_ship_texture(&textures->m_ship) < 0)
	{
		return -1;
	}

	if (g_texture_generate_star_texture(&textures->m_star) < 0)
	{
		return -1;
	}

	if (g_texture_generate_boulder_texture(&textures->m_boulder) < 0)
	{
		return -1;
	}

	return 0;
}

void g_texture_unitialize_data(g_texture_list_t* textures)
{
	if (textures->m_ship)
	{
		al_destroy_bitmap(textures->m_ship);
		textures->m_ship = NULL;
	}

	if (textures->m_star)
	{
		al_destroy_bitmap(textures->m_star);
		textures->m_star = NULL;
	}

	if (textures->m_boulder)
	{
		al_destroy_bitmap(textures->m_boulder);
		textures->m_boulder = NULL;
	}
}
