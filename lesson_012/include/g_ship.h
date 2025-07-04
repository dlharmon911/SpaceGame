#ifndef _HEADER_GUARD_SHIP_H_
#define _HEADER_GUARD_SHIP_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_bullet.h"
#include "g_bullet_array.h"

/// <summary>Amount of rotation when applying ship movement</summary>
static const float G_SHIP_ROTATE_AMOUNT = { (float)ALLEGRO_PI / 70.0f };

/// <summary>Amount of acceleration when applying ship thrust</summary>
static const float G_SHIP_THRUST = { 0.25f };

/// <summary>Amount of acceleration when applying ship reverse thrust relative to forward thrust</summary>
static const float G_SHIP_REVERSE_THRUST_RATIO = { 0.5f };

/// <summary>Data struct for ship entity</summary>
typedef struct g_ship_t
{
	/// <summary>Object data container for the ship entity</summary>
	s_object_t m_object;

	/// <summary>Model data container for the ship entity</summary>
	g_ship_model_t m_ship_model;

	/// <summary>Container for bullet array</summary>
	g_bullet_array_t m_bullet_array;
} g_ship_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='ship'> - pointer to container of ship data</param>
/// <returns>n/a</returns>
void g_ship_set_zero(g_ship_t* ship);

/// <summary>Initializes object and model data</summary>
/// <param name='texture'> - bitmap of ship texture</param>
/// <param name='ship'> - pointer to container of ship data</param>
/// <returns>n/a</returns>
void g_ship_initialize(ALLEGRO_BITMAP* texture, g_ship_t* ship);

/// <summary>Draws ship to display</summary>
/// <param name='ship'> - pointer to container of ship data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_ship_draw(const g_ship_t* ship, int32_t flag);

/// <summary>Updates ship movement/rotation</summary>
/// <param name='bullet'> - pointer to container of ship data</param>
/// <returns>n/a</returns>
void g_ship_update(g_ship_t* ship);

/// <summary>Increase ship acceleration</summary>
/// <param name='bullet'> - pointer to container of ship data</param>
/// <returns>n/a</returns>
void g_ship_forward_thrust(g_ship_t* ship);

/// <summary>Decrease ship acceleration</summary>
/// <param name='bullet'> - pointer to container of ship data</param>
/// <returns>n/a</returns>
void g_ship_reverse_thrust(g_ship_t* ship);

/// <summary>Rotate ship model</summary>
/// <param name='bullet'> - pointer to container of ship data</param>
/// <param name='delta'> - amount of angle change</param>
/// <returns>n/a</returns>
void g_ship_rotate(g_ship_t* ship, float delta);

/// <summary>Fire bullet</summary>
/// <param name='bullet'> - pointer to container of ship data</param>
/// <returns>bool - true on success, false on failure</returns>
bool g_ship_fire_bullet(g_ship_t* ship);

#endif // !_HEADER_GUARD_SHIP_H_
