#ifndef _HEADER_GUARD_COLLISION_H_
#define _HEADER_GUARD_COLLISION_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_boulder.h"
#include "g_boulder_array.h"
#include "g_bullet.h"
#include "g_bullet_array.h"
#include "g_ship.h"

typedef struct g_stats_collision_t
{
	/// <summary>Number of collision checks/frame</summary>
	size_t m_collisions_per_frame;
	/// <summary>Number of collision checks/frame</summary>
	size_t m_full_collisions_per_frame;
} g_stats_collision_t;

/// <summary>Process collisions from bullet array vs boulder_array</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='bullet_array'> - pointer to container of bullet array data</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
bool g_collision_do_boulder_array_vs_bullet_array_collision(g_boulder_array_t* boulder_array, g_bullet_array_t* bullet_array, g_stats_collision_t* stats);

/// <summary>Process collisions from bullet array vs boulder_array</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='ship'> - pointer to container of ship data</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
bool g_collision_do_boulder_array_vs_ship_collision(const g_boulder_array_t* boulder_array, const g_ship_t* ship, g_stats_collision_t* stats);

/// <summary>Process collisions from boulder_array against itself</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
bool g_collision_do_boulder_array_vs_boulder_array_collision(g_boulder_array_t* boulder_array, g_stats_collision_t* stats);

#endif // !_HEADER_GUARD_COLLISION_H_
