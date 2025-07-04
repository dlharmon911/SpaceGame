#ifndef _HEADER_GUARD_BULLET_ARRAY_H_
#define _HEADER_GUARD_BULLET_ARRAY_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_texture_data.h"
#include "g_model_data.h"
#include "g_bullet.h"

enum
{
	/// <summary>Initial maximum number of bullets</summary>
	G_BULLET_INITIAL_MAX_COUNT = 20,

	/// <summary>Maximum number of bullets</summary>
	G_BULLET_MAX_COUNT = 40
};

enum
{
	/// <summary>Status flag default setting</summary>
	G_BULLET_STATUS_DEFAULT = 0,
	/// <summary>Status flag indicating alive</summary>
	G_BULLET_STATUS_LIVE = 1
};

/// <summary>Data struct for the bullet array</summary>
typedef struct g_bullet_node_t
{
	/// <summary>Data container for the bullet entity</summary>
	g_bullet_t m_bullet;
	/// <summary>Status (bit flags) or bullet</summary>
	uint32_t m_status;
} g_bullet_node_t;

/// <summary>Data struct for bullet array</summary>
typedef struct g_bullet_array_t
{
	/// <summary>Current count of bullets that are live in the bullet array</summary>
	size_t m_count;

	/// <summary>Maximum number of bullets the bullet array can hold</summary>
	size_t m_max_count;

	/// <summary>Array to hold bullet array data</summary>
	g_bullet_node_t m_bullet[G_BULLET_MAX_COUNT];
} g_bullet_array_t;

/// <summary>Zero initializes bullet array data</summary>
/// <param name='bullet_array'> - pointer to container of bullet array data</param>
/// <returns>n/a</returns>
void g_bullet_array_set_zero(g_bullet_array_t* bullet_array);

/// <summary>Initializes bullet array object and model data</summary>
/// <param name='texture'> - bitmap of bullet texture</param>
/// <param name='bullet_array'> - pointer to container of bullet array data</param>
/// <returns>n/a</returns>
void g_bullet_array_initialize(ALLEGRO_BITMAP* texture, g_bullet_array_t* bullet_array);

/// <summary>Find first dead bullet and reactivate it</summary>
/// <param name='bullet_array'> - pointer to container of bullet array data</param>
/// <returns>g_bullet_node_t* - pointer to the node of bullet activated, NULL on no available bullet slot</returns>
g_bullet_node_t* g_bullet_array_activate(g_bullet_array_t* bullet_array);

/// <summary>Draws bullet array to display</summary>
/// <param name='boulder_array'> - pointer to container of bullet array data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_bullet_array_draw(const g_bullet_array_t* bullet_array, int32_t flag);

/// <summary>Updates bullet array movement/rotation</summary>
/// <param name='boulder_array'> - pointer to container of bullet array data</param>
/// <returns>n/a</returns>
void g_bullet_array_update(g_bullet_array_t* bullet_array);

/// <summary>Updates bullet array movement/rotation step-wise</summary>
/// <param name='boulder_array'> - pointer to container of bullet array data</param>
/// <returns>n/a</returns>
void g_bullet_array_update_step(g_bullet_array_t* bullet_array);

/// <summary>Fire a bullet to display</summary>
/// <param name='boulder_array'> - pointer to container of bullet array data</param>
/// <param name='player'> - Used to get initial position and facing angle of bullet</param>
/// <returns>bool - true on success, false on failure</returns>
bool g_bullet_array_fire(g_bullet_array_t* bullet_array, const s_object_t* player);

#endif // !_HEADER_GUARD_BULLET_ARRAY_H_
