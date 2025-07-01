#ifndef _HEADER_GUARD_STAR_H_
#define _HEADER_GUARD_STAR_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

/// <summary>Max object speed</summary>
static const float G_STAR_MAX_SPEED = { 4.0f };

/// <summary>Data struct for star entity</summary>
typedef struct g_star_t
{
	/// <summary>Object data container for the star entity</summary>
	s_object_t m_object;

	/// <summary>Model data container for the star entity</summary>
	s_quad_model_t m_star_model;
	float m_z;
} g_star_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='star'> - pointer to container of star data</param>
/// <returns>n/a</returns>
void g_star_set_zero(g_star_t* star);

/// <summary>Initializes object and model data</summary>
/// <param name='texture'> - bitmap of star texture</param>
/// <param name='star'> - pointer to container of star data</param>
/// <param name='scale'> - size multiplier</param>
/// <returns>n/a</returns>
void g_star_initialize(ALLEGRO_BITMAP* texture, g_star_t* star, float scale);

/// <summary>Draws star to display</summary>
/// <param name='star'> - pointer to container of star data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_star_draw(const g_star_t* star, int32_t flag);

/// <summary>Updates star movement/rotation</summary>
/// <param name='star'> - pointer to container of star data</param>
/// <returns>n/a</returns>
void g_star_update(g_star_t* star);

/// <summary>Updates star movement/rotation step-wise</summary>
/// <param name='star'> - pointer to container of star data</param>
/// <returns>n/a</returns>
void g_star_update_step(g_star_t* star);

/// <summary>Constrain to window</summary>
/// <param name='star'> - pointer to container of star data</param>
/// <param name='top_left'> - top left point of window</param>
/// <param name='bottom_right'> - bottom right point of window</param>
/// <returns>bool - true on success, false on failure</returns>
void g_star_apply_window_constraint(g_star_t* star, const s_point_t* top_left, const s_point_t* bottom_right);

#endif // !_HEADER_GUARD_STAR_H_
