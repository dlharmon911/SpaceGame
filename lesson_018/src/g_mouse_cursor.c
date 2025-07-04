#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_star.h"
#include "g_mouse_cursor.h"

void g_mouse_cursor_set_zero(g_mouse_cursor_t* mouse_cursor)
{
	if (!mouse_cursor)
	{
		return;
	}

	g_star_set_zero(&mouse_cursor->m_icon);
	s_point_set_zero(&mouse_cursor->m_position);
	mouse_cursor->m_visible = true;
	mouse_cursor->m_active = true;
}

void g_mouse_cursor_initialize(ALLEGRO_BITMAP* texture, g_mouse_cursor_t* mouse_cursor)
{
	if (!texture)
	{
		return;
	}

	if (!mouse_cursor)
	{
		return;
	}

	g_star_initialize(texture, &mouse_cursor->m_icon, 0.65f);
}

void g_mouse_cursor_set_position(g_mouse_cursor_t* mouse_cursor, const s_point_t* point)
{
	if (!mouse_cursor)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	s_point_set(&mouse_cursor->m_position, point);
}

void g_mouse_cursor_set_position_f(g_mouse_cursor_t* mouse_cursor, float x, float y)
{
	if (!mouse_cursor)
	{
		return;
	}

	s_point_set_f(&mouse_cursor->m_position, x, y);
}

const s_point_t* g_mouse_cursor_get_position(const g_mouse_cursor_t* mouse_cursor)
{
	if (!mouse_cursor)
	{
		return NULL;
	}

	return &mouse_cursor->m_position;
}

void g_mouse_cursor_set_active(g_mouse_cursor_t* mouse_cursor, bool active)
{
	if (!mouse_cursor)
	{
		return;
	}

	mouse_cursor->m_active = active;
}

bool g_mouse_cursor_is_active(const g_mouse_cursor_t* mouse_cursor)
{
	if (!mouse_cursor)
	{
		return false;
	}

	return mouse_cursor->m_active;
}

void g_mouse_cursor_set_visible(g_mouse_cursor_t* mouse_cursor, bool visible)
{
	if (!mouse_cursor)
	{
		return;
	}

	mouse_cursor->m_visible = visible;
}

bool g_mouse_cursor_is_visible(const g_mouse_cursor_t* mouse_cursor)
{
	if (!mouse_cursor)
	{
		return false;
	}

	return mouse_cursor->m_visible;
}

void g_mouse_cursor_draw(const g_mouse_cursor_t* mouse_cursor, int32_t flag)
{
	ALLEGRO_TRANSFORM transform = { 0 };

	if (!mouse_cursor)
	{
		return;
	}

	if (mouse_cursor->m_active && mouse_cursor->m_visible)
	{
		al_identity_transform(&transform);
		s_point_translate(&transform, &mouse_cursor->m_position);
		al_use_transform(&transform);
		g_star_draw(&mouse_cursor->m_icon, flag);
	}
}
