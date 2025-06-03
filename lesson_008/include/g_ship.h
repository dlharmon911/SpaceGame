#ifndef _HEADER_GUARD_SHIP_H_
#define _HEADER_GUARD_SHIP_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_textures.h"
#include "g_models.h"

/// <summary>Amount of rotation when applying ship movement</summary>
static const float G_SHIP_ROTATE_AMOUNT = { (float)ALLEGRO_PI / 70.0f };

/// <summary>Amount of acceleration when applying ship thrust</summary>
static const float G_SHIP_THRUST = { 0.25f };

typedef struct g_ship_t
{
	s_object_t m_object;
	g_ship_model_t m_ship_model;
} g_ship_t;

void g_ship_zero_initialize_data(g_ship_t* ship);
void g_ship_initialize(const g_texture_list_t* texture_list, g_ship_t* ship);
void g_ship_draw(const g_ship_t* ship, int32_t flag);
void g_ship_update(g_ship_t* ship);
void g_ship_forward_thrust(g_ship_t* ship);
void g_ship_reverse_thrust(g_ship_t* ship);
void g_ship_rotate(g_ship_t* ship, float delta);

#endif // !_HEADER_GUARD_SHIP_H_
