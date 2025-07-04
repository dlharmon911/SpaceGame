#ifndef _HEADER_GUARD_TEXTURES_H_
#define _HEADER_GUARD_TEXTURES_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

static const bool G_TEXTURES_GENERATE_NEW = { false };

static const bool G_TEXTURES_SAVE_TO_FILE = { false };

/// <summary>Size of the bitmap for the ship</summary>
static const s_point_t G_TEXTURE_SHIP_SIZE = { 64.0f, 64.0f };

/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_STAR_SIZE = { 256.0f, 256.0f };
/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_BOULDER_SIZE = { 256.0f, 256.0f };

static const char* G_TEXTURE_ARCHIVE_FILENAME = "assets.7z";

typedef struct g_texture_data_t
{
	ALLEGRO_BITMAP* m_ship;
	ALLEGRO_BITMAP* m_star;
	ALLEGRO_BITMAP* m_boulder;
} g_texture_data_t;

int32_t g_texture_data_load(g_texture_data_t* textures, const char* filename);

void g_texture_data_set_zero(g_texture_data_t* textures);
int32_t g_texture_data_generate(g_texture_data_t* textures);
void g_texture_data_destroy(g_texture_data_t* textures);

int32_t g_texture_generate_ship_texture(ALLEGRO_BITMAP** bitmap);
int32_t g_texture_generate_star_texture(ALLEGRO_BITMAP** bitmap);
int32_t g_texture_generate_boulder_texture(ALLEGRO_BITMAP** bitmap);

#endif // !_HEADER_GUARD_TEXTURES_H_
