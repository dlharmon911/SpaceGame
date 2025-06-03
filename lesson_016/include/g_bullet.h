#ifndef _HEADER_GUARD_BULLET_H_
#define _HEADER_GUARD_BULLET_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

/// <summary>Initial speed of bullet</summary>
static const float G_BULLET_SPEED = 12.0f;

/// <summary>Maximum speed of bullet</summary>
static const float G_BULLET_MAX_SPEED = 20.0f;

/// <summary>[U, V] position on the texture bitmap</summary>
static const s_point_t G_BULLET_TEXTURE_UV = { 47.0f, 0.0f };

/// <summary>[U, V] size of the texture bitmap</summary>
static const s_point_t G_BULLET_TEXTURE_UV_SIZE = { 1.0f, 4.0f };

/// <summary>Size of the bullet model</summary>
static const s_point_t G_BULLET_SIZE = { 4.0f, 1.0f };

/// <summary>Sizing multiplier of the bullet model</summary>
static const float G_BULLET_SIZE_SCALE = { 3.0f };


/// <summary>Maximum number of update steps before automatically die</summary>
static const size_t G_BULLET_ITERATIONS = 48;



/// <summary>Data struct for bullet entity</summary>
typedef struct g_bullet_t
{
	/// <summary>Object data container for the bullet entity</summary>
	s_object_t m_object;
	/// <summary>Model data container for the bullet entity</summary>
	s_quad_model_t m_bullet_model;
	/// <summary>Number of updates before it dies automatically</summary>
	size_t m_iterations;
} g_bullet_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_zero_initialize_data(g_bullet_t* bullet);

/// <summary>Initializes object and model data</summary>
/// <param name='texture'> - bitmap of bullet texture</param>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_initialize(ALLEGRO_BITMAP* texture, g_bullet_t* bullet);

/// <summary>Resets bullet position/rotation to zero</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_reset(g_bullet_t* bullet);

/// <summary>Draws bullet to display</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_bullet_draw(const g_bullet_t* bullet, int32_t flag);

/// <summary>Updates bullet movement/rotation</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_update(g_bullet_t* bullet);

/// <summary>Updates bullet movement/rotation step-wise</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_update_step(g_bullet_t* bullet);

/// <summary>Constrain to window</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <param name='top_left'> - top left point of window</param>
/// <param name='bottom_right'> - bottom right point of window</param>
/// <returns>bool - true on success, false on failure</returns>
void g_bullet_apply_window_constraint(g_bullet_t* bullet, const s_point_t* top_left, const s_point_t* bottom_right);

#endif // !_HEADER_GUARD_BULLET_H_
