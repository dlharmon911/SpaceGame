#include <allegro5/allegro5.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"

int32_t g_texture_generate_ship_texture(ALLEGRO_BITMAP** bitmap);
int32_t g_texture_generate_star_texture(ALLEGRO_BITMAP** bitmap);
int32_t g_texture_generate_boulder_texture(ALLEGRO_BITMAP** bitmap);

static const char* g_texture_filenames[G_TEXTURE_COUNT] =
{
	"star.png",
	"ship.png",
	"boulder.png"
};

void g_texture_zero_initialize_data(g_texture_list_t* textures)
{
	if (!textures)
	{
		return;
	}

	for (size_t i = 0; i < G_TEXTURE_COUNT; ++i)
	{
		textures->m_texture[i] = NULL;
	}
}

static int32_t g_load_texture_from_archive(g_texture_list_t* textures)
{
	for (size_t i = 0; i < G_TEXTURE_COUNT; ++i)
	{
		textures->m_texture[i] = al_load_bitmap(g_texture_filenames[i]);

		if (!textures->m_texture[i])
		{
			return -1;
		}
	}

	return 0;
}

static int32_t g_save_textures(const g_texture_list_t* textures)
{
	for (size_t i = 0; i < G_TEXTURE_COUNT; ++i)
	{
		const char* filename = g_texture_filenames[i];

		if (!al_save_bitmap(filename, textures->m_texture[i]))
		{
			return -1;
		}
	}

	return 0;
}

int32_t g_load_textures(g_texture_list_t* textures, const char* filename)
{
	const ALLEGRO_FILE_INTERFACE* file_interface = al_get_new_file_interface();
	int32_t rv = -1;

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
	int32_t(*function_ptr[])(ALLEGRO_BITMAP**) =
	{
		g_texture_generate_star_texture,
		g_texture_generate_ship_texture,
		g_texture_generate_boulder_texture
	};

	for (size_t i = 0; i < G_TEXTURE_COUNT; ++i)
	{
		if (function_ptr[i](&textures->m_texture[i]) < 0)
		{
			return -1;
		}
	}

	if (G_TEXTURES_SAVE_TO_FILE && g_save_textures(textures) < 0)
	{
		return -1;
	}

	return 0;
}

void g_texture_unitialize_data(g_texture_list_t* textures)
{
	for (size_t i = 0; i < G_TEXTURE_COUNT; ++i)
	{
		if (textures->m_texture[i])
		{
			al_destroy_bitmap(textures->m_texture[i]);
			textures->m_texture[i] = NULL;
		}
	}
}
