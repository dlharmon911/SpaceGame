#ifndef _HEADER_GUARD_MODELS_H_
#define _HEADER_GUARD_MODELS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

/// <summary>Size of the bitmap for the ship</summary>
static const s_point_t G_SHIP_SIZE = { 48.0f, 64.0f };

/// <summary>Center point of rotation with respect to ship size</summary>
static const s_point_t G_SHIP_CENTER_POINT = { 0.5f, 0.85f };

enum
{
	G_SHIP_VERTEX_COUNT = 4,
	G_SHIP_OUTLINE_VERTEX_COUNT = 4,
	G_SHIP_TRIANGLE_COUNT = 2
};

enum
{
	G_STAR_VERTEX_COUNT = 4,
	G_STAR_OUTLINE_VERTEX_COUNT = 4,
	G_STAR_TRIANGLE_COUNT = 2
};

/// <summary>Constant for the star size</summary>
static const s_point_t G_TEXTURE_STAR_CHUNK_SIZE = { 32.0f, 32.0f };

typedef struct g_ship_model_t
{
	int32_t m_indices[S_TRIANGLE_POINT_COUNT * G_SHIP_TRIANGLE_COUNT];
	s_vertex_t m_vertices[G_SHIP_VERTEX_COUNT];
	int32_t m_outline[G_SHIP_OUTLINE_VERTEX_COUNT];
} g_ship_model_t;

typedef struct g_star_model_t
{
	int32_t m_indices[S_TRIANGLE_POINT_COUNT * G_STAR_TRIANGLE_COUNT];
	s_vertex_t m_vertices[G_STAR_VERTEX_COUNT];
	int32_t m_outline[G_STAR_OUTLINE_VERTEX_COUNT];
} g_star_model_t;

void g_model_generate_ship_model(g_ship_model_t* ship_model, s_model_t* model, ALLEGRO_BITMAP* texture);
void g_model_generate_star_model(g_star_model_t* star_model, s_model_t* model, ALLEGRO_BITMAP* texture, float z);

#endif // !_HEADER_GUARD_MODELS_H_
