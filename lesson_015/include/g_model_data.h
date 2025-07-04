#ifndef _HEADER_GUARD_MODELS_H_
#define _HEADER_GUARD_MODELS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

/// <summary>Size of the bitmap for the ship</summary>
static const s_point_t G_SHIP_SIZE = { 48.0f, 64.0f };

/// <summary>Size of the bitmap for the ship</summary>
static const float G_SHIP_SIZE_SCALE = { 0.75f };

/// <summary>Center point of rotation with respect to ship size</summary>
static const s_point_t G_SHIP_CENTER_POINT = { 0.5f, 0.85f };

enum
{
	/// <summary>Vertex count</summary>
	G_SHIP_VERTEX_COUNT = 4,

	/// <summary>Vertex count - outline only</summary>
	G_SHIP_OUTLINE_VERTEX_COUNT = 4,

	/// <summary>Triangle count</summary>
	G_SHIP_TRIANGLE_COUNT = 2
};

enum
{
	/// <summary>Vertex count</summary>
	G_BOULDER_VERTEX_COUNT = 17,

	/// <summary>Vertex count - outline only</summary>
	G_BOULDER_OUTLINE_VERTEX_COUNT = 16,

	/// <summary>Triangle count</summary>
	G_BOULDER_TRIANGLE_COUNT = 16,
};

/// <summary>Constant for the star size</summary>
static const s_point_t G_TEXTURE_STAR_CHUNK_SIZE = { 32.0f, 32.0f };

/// <summary>Model data for ship</summary>
typedef struct g_ship_model_t
{
	/// <summary>Index array for vertices</summary>
	int32_t m_indices[S_TRIANGLE_POINT_COUNT * G_SHIP_TRIANGLE_COUNT];

	/// <summary>Vertex array for triangles</summary>
	s_vertex_t m_vertices[G_SHIP_VERTEX_COUNT];

	/// <summary>Vertex array for outline</summary>
	int32_t m_outline[G_SHIP_OUTLINE_VERTEX_COUNT];
} g_ship_model_t;

/// <summary>Model data for boulder</summary>
typedef struct g_boulder_model_t
{
	/// <summary>Index array for vertices</summary>
	int32_t m_indices[S_TRIANGLE_POINT_COUNT * G_BOULDER_TRIANGLE_COUNT];

	/// <summary>Vertex array for triangles</summary>
	s_vertex_t m_vertices[G_BOULDER_VERTEX_COUNT];

	/// <summary>Vertex array for outline</summary>
	int32_t m_outline[G_BOULDER_OUTLINE_VERTEX_COUNT];
} g_boulder_model_t;

/// <summary>Populate ship model information</summary>
/// <param name='ship_model'> - data for the model</param>
/// <param name='model'> - data for the spacelib model (pointers)</param>
/// <param name='texture'> - bitmap for the model</param>
/// <returns>n/a</returns>
void g_model_generate_ship_model(g_ship_model_t* ship_model, s_model_t* model, ALLEGRO_BITMAP* texture);

/// <summary>Populate star model information</summary>
/// <param name='star_model'> - data for the model</param>
/// <param name='model'> - data for the spacelib model (pointers)</param>
/// <param name='texture'> - bitmap for the model</param>
/// <param name='scale'> - size multiplier</param>
/// <returns>n/a</returns>
void g_model_generate_star_model(s_quad_model_t* star_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale);

/// <summary>Populate boulder model information</summary>
/// <param name='boulder_model'> - data for the model</param>
/// <param name='model'> - data for the spacelib model (pointers)</param>
/// <param name='texture'> - bitmap for the model</param>
/// <param name='scale'> - size multiplier</param>
/// <returns>n/a</returns>
void g_model_generate_boulder_model(g_boulder_model_t* boulder_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale, float* radius);

/// <summary>Populate bullet model information</summary>
/// <param name='bullet_model'> - data for the model</param>
/// <param name='model'> - data for the spacelib model (pointers)</param>
/// <param name='texture'> - bitmap for the model</param>
/// <param name='scale'> - size multiplier</param>
/// <returns>n/a</returns>
void g_model_generate_bullet_model(s_quad_model_t* star_model, s_model_t* model, ALLEGRO_BITMAP* texture, float scale);

#endif // !_HEADER_GUARD_MODELS_H_
