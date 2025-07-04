#ifndef _HEADER_GUARD_BULLET_H_
#define _HEADER_GUARD_BULLET_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_texture_data.h"
#include "g_model_data.h"

/// <summary>Initial speed of bullet</summary>
static const float G_BULLET_SPEED = 6.0f;

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

/// <summary>Data struct for bullet entity</summary>
typedef struct g_bullet_t
{
	/// <summary>Object data container for the bullet entity</summary>
	s_object_t m_object;

	/// <summary>Model data container for the bullet entity</summary>
	s_quad_model_t m_bullet_model;
} g_bullet_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='bullet'> - pointer to container of bullet data</param>
/// <returns>n/a</returns>
void g_bullet_set_zero(g_bullet_t* bullet);

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

#endif // !_HEADER_GUARD_BULLET_H_
