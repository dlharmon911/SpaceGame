#ifndef _HEADER_GUARD_BOULDER_H_
#define _HEADER_GUARD_BOULDER_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

/// <summary>Initial starting movement velocity maximum</summary>
static const float G_BOULDER_START_VELOCITY_MAX = 0.8f;

/// <summary>Initial starting movement velocity minimum</summary>
static const float G_BOULDER_START_VELOCITY_MIN = 0.5f;

/// <summary>Initial starting rotational velocity maximum</summary>
static const float G_BOULDER_START_ROTATE_VELOCITY_MAX = 0.025f;

/// <summary>Initial starting rotational velocity minimum</summary>
static const float G_BOULDER_START_ROTATE_VELOCITY_MIN = 0.005f;

/// <summary>Scaling maximum value</summary>
static const float G_BOULDER_SCALE_MAX = 0.9f;

/// <summary>Scaling minimum value</summary>
static const float G_BOULDER_SCALE_MIN = 0.4f;

/// <summary>Scaling minimum for shot boulder</summary>
static const float G_BOULDER_SHOT_SCALE_MIN = 0.2f;

/// <summary>Scaling multiplier for children boulders when shot</summary>
static const float G_BOULDER_SHOT_SCALE_MULTIPLIER = 0.6f;

/// <summary>Data struct for boulder entity</summary>
typedef struct g_boulder_t
{
	/// <summary>Object data container for the boulder entity</summary>
	s_object_t m_object;
	/// <summary>Model data container for the boulder entity</summary>
	g_boulder_model_t m_boulder_model;
	/// <summary>Scale ratio of boulder compared to full size</summary>
	float m_scale;
	/// <summary>Maximum radius of each vertex from center</summary>
	float m_radius;
} g_boulder_t;

/// <summary>Zero initializes boulder data</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <returns>n/a</returns>
void g_boulder_set_zero(g_boulder_t* boulder);

/// <summary>Initializes boulder model data</summary>
/// <param name='texture'> - bitmap of boulder texture</param>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <param name='scale'> - multiplier of boulder size</param>
/// <returns>n/a</returns>
void g_boulder_initialize(ALLEGRO_BITMAP* texture, g_boulder_t* boulder, float scale);

/// <summary>Resets boulder position/rotation to zero</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <returns>n/a</returns>
void g_boulder_reset(g_boulder_t* boulder);

/// <summary>Draws boulder to display</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_boulder_draw(const g_boulder_t* boulder, int32_t flag);

/// <summary>Updates boulder movement/rotation</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <returns>n/a</returns>
void g_boulder_update(g_boulder_t* boulder);

/// <summary>Updates boulder movement/rotation step-wise</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <returns>n/a</returns>
void g_boulder_update_step(g_boulder_t* boulder);

/// <summary>Constrain to window</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <param name='top_left'> - top left point of window</param>
/// <param name='bottom_right'> - bottom right point of window</param>
/// <returns>bool - true on success, false on failure</returns>
void g_boulder_apply_window_constraint(g_boulder_t* boulder, const s_point_t* top_left, const s_point_t* bottom_right);

#endif // !_HEADER_GUARD_BOULDER_H_
