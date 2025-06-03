#ifndef _HEADER_GUARD_MOUSE_CURSOR_H_
#define _HEADER_GUARD_MOUSE_CURSOR_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_star.h"

typedef struct g_mouse_cursor_t
{
	g_star_t m_icon;
	s_point_t m_position;
	bool m_visible;
	bool m_active;
} g_mouse_cursor_t;

void g_mouse_cursor_zero_initialize_data(g_mouse_cursor_t* mouse_cursor);
void g_mouse_cursor_initialize(ALLEGRO_BITMAP* texture, g_mouse_cursor_t* mouse_cursor);
void g_mouse_cursor_set_position(g_mouse_cursor_t* mouse_cursor, const s_point_t* point);
void g_mouse_cursor_set_position_f(g_mouse_cursor_t* mouse_cursor, float x, float y);
const s_point_t* g_mouse_cursor_get_position(const g_mouse_cursor_t* mouse_cursor);
void g_mouse_cursor_set_active(g_mouse_cursor_t* mouse_cursor, bool active);
bool g_mouse_cursor_is_active(const g_mouse_cursor_t* mouse_cursor);
void g_mouse_cursor_set_visible(g_mouse_cursor_t* mouse_cursor, bool visible);
bool g_mouse_cursor_is_visible(const g_mouse_cursor_t* mouse_cursor);
void g_mouse_cursor_draw(const g_mouse_cursor_t* mouse_cursor, int32_t flag);

#endif // !_HEADER_GUARD_MOUSE_CURSOR_H_
