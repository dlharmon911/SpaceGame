#ifndef _HEADER_GUARD_RADAR_H_
#define _HEADER_GUARD_RADAR_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"
#include "g_boulder.h"
#include "g_boulder_array.h"

static const ALLEGRO_COLOR G_RADAR_COLOR_TEXT = { 0.75f, 0.75f, 0.75f, 1.0f };
static const float G_RADAR_LENGTH_MAX = 1200.0f;
static const float G_RADAR_ROTATION_AMOUNT = 0.035f;
static const float G_RADAR_LENGTH_EDGE_MARGIN = 16.0f;
static const float G_RADAR_TEXT_MARGIN = 4.0f;
static const s_point_t G_RADAR_SIZE = { 128.0f, 128.0f };
static const s_point_t G_RADAR_SIZE_HALF = { 64.0f, 64.0f };
static const s_point_t G_RADAR_MARGIN = { 16.0f, 16.0f };
static const float G_RADAR_SCALE = 2.0f;
static const float G_RADAR_SCALE_TEXT = 2.75f;

/// <summary>Data struct for radar entity</summary>
typedef struct g_radar_t
{
	s_model_t m_model[G_MODEL_RADAR_MODEL_COUNT];
	s_quad_model_t m_quad_model[G_MODEL_RADAR_MODEL_COUNT];
	s_point_t m_position;
	const g_boulder_array_t* m_boulder_array;
	const s_point_t* m_ship_center;
	const ALLEGRO_FONT* m_font;
	float m_angle;
} g_radar_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='radar'> - pointer to container of radar data</param>
/// <returns>n/a</returns>
void g_radar_set_zero(g_radar_t* radar);

/// <summary>Initializes object and model data</summary>
/// <param name='texture'> - bitmap of radar texture</param>
/// <param name='radar'> - pointer to container of radar data</param>
/// <returns>n/a</returns>
void g_radar_initialize(ALLEGRO_BITMAP* texture, g_radar_t* radar);

/// <summary>Draws radar to display</summary>
/// <param name='radar'> - pointer to container of radar data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void g_radar_draw(const g_radar_t* radar, int32_t flag);

/// <summary>Update radar sweep motion</summary>
/// <param name='radar'> - pointer to container of radar data</param>
/// <returns>n/a</returns>
void g_radar_update(g_radar_t* radar);

#endif // !_HEADER_GUARD_RADAR_H_
