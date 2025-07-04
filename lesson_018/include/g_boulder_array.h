#ifndef _HEADER_GUARD_BOULDER_ARRAY_H_
#define _HEADER_GUARD_BOULDER_ARRAY_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_boulder.h"

enum
{
	/// <summary>Initial capacity of boulder array capacity</summary>
	G_BOULDER_INITIAL_MAX_COUNT = 20,

	G_BOULDER_MAX_COUNT = 4 * G_BOULDER_INITIAL_MAX_COUNT
};

enum G_BOULDER_NODE_STATUS_FLAGS
{
	/// <summary>Status flag default setting</summary>
	G_BOULDER_STATUS_UNINITIALIZED = 0,
	/// <summary>Status flag default setting</summary>
	G_BOULDER_STATUS_INITIALIZED = 1,
	/// <summary>Status flag indicating alive</summary>
	G_BOULDER_STATUS_LIVE = 2
};

/// <summary>Data struct for internal vector of the boulder array</summary>
typedef struct g_boulder_node_t
{
	/// <summary>Data container for the boulder entity</summary>
	g_boulder_t m_boulder;
	/// <summary>Status (bit flags) or boulder</summary>
	uint32_t m_status;
} g_boulder_node_t;

/// <summary>Data struct for boulder array</summary>
typedef struct g_boulder_array_t
{
	/// <summary>Current count of boulders that are live in the boulder array</summary>
	size_t m_count;

	/// <summary>Maximum number of boulders the boulder array can hold</summary>
	size_t m_max_count;

	/// <summary>Array to hold boulder array data</summary>
	g_boulder_node_t m_boulder[G_BOULDER_MAX_COUNT];
} g_boulder_array_t;

/// <summary>Zero initializes boulder array data</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_set_zero(g_boulder_array_t* boulder_array);

/// <summary>Draws boulder array to display</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_boulder_array_draw(const g_boulder_array_t* boulder_array, int32_t flag);

/// <summary>Returns first dead boulder or adds a new boulder to vector and returns that</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>g_boulder_node_t* - boulder node</returns>
g_boulder_node_t* g_boulder_array_find_first_dead_boulder(g_boulder_array_t* boulder_array);

/// <summary>Populates boulder data (position, velocity, rotation)</summary>
/// <param name='boulder'> - pointer to container of boulder data</param>
/// <returns>n/a</returns>
void g_boulder_array_populate_boulder_data(g_boulder_t* boulder);

/// <summary>Initialize model and randomly place boulders</summary>
/// <param name='texture'> - bitmap of boulder texture</param>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_scatter(ALLEGRO_BITMAP* texture, g_boulder_array_t* boulder_array);

/// <summary>Updates boulder array movement/rotation</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_update(g_boulder_array_t* boulder_array);

/// <summary>Updates boulder array movement/rotation step-wise</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_update_step(g_boulder_array_t* boulder_array);

/// <summary>Process a collision which takes current boulder and create two smaller versions</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='boulder_node'> - the container of the boulder that was hit</param>
/// <param name='velocity'> - the velocity of the boulder used to determine direction of new boulders</param>
/// <returns>n/a</returns>
void g_boulder_array_process_collisions(g_boulder_array_t* boulder_array);

/// <summary>Constrain to window</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='top_left'> - top left point of window</param>
/// <param name='bottom_right'> - bottom right point of window</param>
/// <returns>bool - true on success, false on failure</returns>
void g_boulder_array_apply_window_constraint(g_boulder_array_t* boulder_array, const s_point_t* top_left, const s_point_t* bottom_right);

#endif // !_HEADER_GUARD_BOULDER_ARRAY_H_
