#ifndef _HEADER_GUARD_STAR_ARRAY_H_
#define _HEADER_GUARD_STAR_ARRAY_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"
#include "g_star.h"

enum
{
	/// <summary>Star count multiplier</summary>
	G_STAR_MULTIPLIER = 2,

	/// <summary>Number of stars in layer 1</summary>
	G_STAR_LAYER_01 = 5 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 2</summary>
	G_STAR_LAYER_02 = 10 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 3</summary>
	G_STAR_LAYER_03 = 20 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 4</summary>
	G_STAR_LAYER_04 = 40 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 5</summary>
	G_STAR_LAYER_05 = 80 * G_STAR_MULTIPLIER,

	/// <summary>Total number of stars</summary>
	G_STAR_COUNT = G_STAR_LAYER_01 + G_STAR_LAYER_02 + G_STAR_LAYER_03 + G_STAR_LAYER_04 + G_STAR_LAYER_05
};

/// <summary>Multiplier of ship speed</summary>
static const float G_STAR_SPEED = 0.125f;

/// <summary>Data struct for the star array</summary>
typedef struct g_star_array_t
{
	/// <summary>Size of star array</summary>
	size_t m_count;
	/// <summary>Array for star entity</summary>
	g_star_t m_star[G_STAR_COUNT];
} g_star_array_t;

/// <summary>Zero initializes star array data</summary>
/// <param name='star_array'> - pointer to container of star array data</param>
/// <returns>n/a</returns>
void g_star_array_zero_initialize_data(g_star_array_t* star_array);

/// <summary>Draws star array to display</summary>
/// <param name='star_array'> - pointer to container of star array data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_star_array_draw(const g_star_array_t* star_array, int32_t flag);

/// <summary>Draws star array to display</summary>
/// <param name='texture'> - bitmap of bullet texture</param>
/// <param name='star_array'> - pointer to container of star array data</param>
/// <returns>n/a</returns>
void g_star_array_scatter(ALLEGRO_BITMAP* texture, g_star_array_t* star_array);

/// <summary>Updates star array movement/rotation</summary>
/// <param name='star_array'> - pointer to container of star array data</param>
/// <param name='ship_velocity'> - used to determine direction and amount of star velocity</param>
/// <returns>n/a</returns>
void g_star_array_update(g_star_array_t* star_array, const s_point_t* ship_velocity);

/// <summary>Updates star array movement/rotation step-wise</summary>
/// <param name='star_array'> - pointer to container of star array data</param>
/// <param name='ship_velocity'> - used to determine direction and amount of star velocity</param>
/// <returns>n/a</returns>
void g_star_array_update_step(g_star_array_t* star_array, const s_point_t* ship_velocity);

#endif // !_HEADER_GUARD_STAR_ARRAY_H_
