#ifndef _HEADER_GUARD_STAR_ARRAY_H_
#define _HEADER_GUARD_STAR_ARRAY_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_star.h"

enum
{
	/// <summary>Star count multiplier</summary>
	G_STAR_MULTIPLIER = 1,

	/// <summary>Number of stars in layer 1</summary>
	G_STAR_LAYER_01 = 10 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 2</summary>
	G_STAR_LAYER_02 = 20 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 3</summary>
	G_STAR_LAYER_03 = 40 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 4</summary>
	G_STAR_LAYER_04 = 80 * G_STAR_MULTIPLIER,

	/// <summary>Number of stars in layer 5</summary>
	G_STAR_LAYER_05 = 160 * G_STAR_MULTIPLIER,

	/// <summary>Total number of stars</summary>
	G_STAR_COUNT = G_STAR_LAYER_01 + G_STAR_LAYER_02 + G_STAR_LAYER_03 + G_STAR_LAYER_04 + G_STAR_LAYER_05
};

/// <summary>Multiplier of ship speed</summary>
static const float G_STAR_SPEED = 0.125f;

typedef struct g_star_array_t
{
	size_t m_count;
	g_star_t m_star[G_STAR_COUNT];
} g_star_array_t;

void g_star_array_set_zero(g_star_array_t* star_array);
void g_star_array_draw(const g_star_array_t* star_array, int32_t flag);
void g_star_array_scatter(const g_texture_data_t* texture_list, g_star_array_t* star_array);
void g_star_array_update(g_star_array_t* star_array, const s_point_t* ship_velocity);

#endif // !_HEADER_GUARD_STAR_ARRAY_H_
