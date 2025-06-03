#ifndef _HEADER_GUARD_BOULDER_H_
#define _HEADER_GUARD_BOULDER_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

static const float G_BOULDER_START_VELOCITY_MAX = 0.8f;
static const float G_BOULDER_START_VELOCITY_MIN = 0.5f;
static const float G_BOULDER_START_ROTATE_VELOCITY_MAX = 0.025f;
static const float G_BOULDER_START_ROTATE_VELOCITY_MIN = 0.005f;
static const float G_BOULDER_SCALE_MAX = 0.9f;
static const float G_BOULDER_SCALE_MIN = 0.4f;

typedef struct g_boulder_t
{
	s_object_t m_object;
	g_boulder_model_t m_boulder_model;
} g_boulder_t;

void g_boulder_zero_initialize_data(g_boulder_t* boulder);
void g_boulder_initialize(ALLEGRO_BITMAP* texture, g_boulder_t* boulder, float scale);
void g_boulder_draw(const g_boulder_t* boulder, int32_t flag);
void g_boulder_update(g_boulder_t* boulder);

#endif // !_HEADER_GUARD_BOULDER_H_
