#include <allegro5/allegro5.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
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

static int32_t g_load_texture_from_archive(g_texture_list_t* textures)
{
	typedef struct file_list_t
	{
		const char* m_filename;
		ALLEGRO_BITMAP** m_bitmap;
	} file_list_t;

	file_list_t list[] =
	{
		{ "star.png", &textures->m_star},
		{ "ship.png", &textures->m_ship},
		{ "boulder.png", &textures->m_boulder},
		{ NULL, NULL}
	};
	file_list_t* ptr = list;

	while (ptr->m_filename)
	{
		*ptr->m_bitmap = al_load_bitmap(ptr->m_filename);

		if (!*ptr->m_bitmap)
		{
			return -1;
		}

		++ptr;
	}

	return 0;
}

int32_t g_load_textures(g_texture_list_t* textures, const char* filename)
{
	const ALLEGRO_FILE_INTERFACE* file_interface = al_get_new_file_interface();
	int32_t rv = 0;

	if (PHYSFS_mount(filename, NULL, 1))
	{
		al_set_physfs_file_interface();

		rv = g_load_texture_from_archive(textures);

		PHYSFS_unmount(filename);
	}

	al_set_new_file_interface(file_interface);

	return rv;
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
