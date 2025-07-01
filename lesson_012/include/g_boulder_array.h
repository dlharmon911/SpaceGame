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
	G_BOULDER_INITIAL_COUNT = 20
};

/// <summary>Data struct for internal vector of the boulder array</summary>
typedef struct g_boulder_node_t
{
	/// <summary>Data container for the boulder entity</summary>
	g_boulder_t m_boulder;

	/// <summary>Status (bit flags) or boulder</summary>
	int32_t m_status;
} g_boulder_node_t;

/// <summary>Data struct for boulder array</summary>
typedef struct g_boulder_array_t
{
	/// <summary>Vector to hold boulder array data</summary>
	s_vector_t* m_boulder_list;
} g_boulder_array_t;

/// <summary>Zero initializes boulder array data</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_set_zero(g_boulder_array_t* boulder_array);

/// <summary>Initializes boulder array vector</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='initial_size'> - initial size of internal vector</param>
/// <returns>int32_t - 0 on success, -1 on failure</returns>
int32_t g_boulder_array_initialize(g_boulder_array_t* boulder_array, size_t initial_size);

/// <summary>Clear and release internal vector</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_free(g_boulder_array_t* boulder_array);

/// <summary>Draws boulder array to display</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_boulder_array_draw(const g_boulder_array_t* boulder_array, int32_t flag);

/// <summary>Initialize model and randomly place boulders</summary>
/// <param name='texture'> - bitmap of bullet texture</param>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_scatter(ALLEGRO_BITMAP* texture, g_boulder_array_t* boulder_array);

/// <summary>Updates boulder array movement/rotation</summary>
/// <param name='boulder_array'> - pointer to container of boulder array data</param>
/// <returns>n/a</returns>
void g_boulder_array_update(g_boulder_array_t* boulder_array);

#endif // !_HEADER_GUARD_BOULDER_ARRAY_H_
