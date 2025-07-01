#ifndef _HEADER_GUARD_TEXTURES_H_
#define _HEADER_GUARD_TEXTURES_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

/// <summary>File name for texture assets</summary>
static const char* G_TEXTURE_ARCHIVE_FILENAME = "assets.7z";

/// <summary>Flag to generate new textures instead of loading from file</summary>
static const bool G_TEXTURES_GENERATE_NEW = { true };

/// <summary>Flag to save newly generated textures to file</summary>
static const bool G_TEXTURES_SAVE_TO_FILE = { false };

/// <summary>Size of the bitmap for the ship</summary>
static const s_point_t G_TEXTURE_SHIP_SIZE = { 64.0f, 64.0f};

/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_STAR_SIZE = { 256.0f, 256.0f};

/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_BOULDER_SIZE = { 256.0f, 256.0f };

/// <summary>Size of the bitmap for the star</summary>
static const s_point_t G_TEXTURE_RADAR_SIZE = { 256.0f, 256.0f };

enum G_TEXTURE_ARRAY_INDEXES
{
	/// <summary>Index for star texture</summary>
	G_TEXTURE_STAR,
	/// <summary>Index for ship texture</summary>
	G_TEXTURE_SHIP,
	/// <summary>Index for boulder texture</summary>
	G_TEXTURE_BOULDER,
	/// <summary>Index for radar texture</summary>
	G_TEXTURE_RADAR,
	/// <summary>Total texture count</summary>
	G_TEXTURE_COUNT
};

/// <summary>Data struct for texture array</summary>
typedef struct g_texture_list_t
{
	/// <summary>Bitmap array of textures</summary>
	ALLEGRO_BITMAP* m_texture[G_TEXTURE_COUNT];
} g_texture_list_t;

/// <summary>Zero initializes texture array data</summary>
/// <param name='textures'> - struct of bitmap array</param>
/// <returns>n/a</returns>
void g_texture_set_zero(g_texture_list_t* textures);

/// <summary>Load texture bitmaps from file</summary>
/// <param name='textures'> - struct of bitmap array</param>
/// <param name='filename'> - Name of the archive file</param>
/// <returns>int32_t - 0 on success, -1 on failure</returns>
int32_t g_load_textures(g_texture_list_t* textures, const char* filename);

/// <summary>Generate texture bitmaps</summary>
/// <param name='textures'> - struct of bitmap array</param>
/// <returns>int32_t - 0 on success, -1 on failure</returns>
int32_t g_texture(g_texture_list_t* textures);

/// <summary>Release bitmap memory</summary>
/// <param name='textures'> - struct of bitmap array</param>
/// <returns>n/a</returns>
void g_texture_unitialize_data(g_texture_list_t* textures);

#endif // !_HEADER_GUARD_TEXTURES_H_
