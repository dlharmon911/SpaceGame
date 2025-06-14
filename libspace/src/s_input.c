#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_input.h"

static uint8_t s_input_key_buttons[S_KEY_BUTTON_MAX];
static uint8_t s_input_mouse_buttons[S_MOUSE_BUTTON_MAX];
static s_point_t s_input_mouse_axis = { 0.0f, 0.0f };

enum
{
	S_BUTTON_DEFAULT,
	S_BUTTON_PRESSED = 0x01,
	S_BUTTON_CHANGED = 0x02
};

void s_input_set_key_button_array_index(size_t index, bool pressed)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return;
	}

	if (pressed)
	{
		s_input_key_buttons[index] = (S_BUTTON_PRESSED | S_BUTTON_CHANGED);
	}
	else
	{
		s_input_key_buttons[index] = S_BUTTON_CHANGED;
	}
}

uint8_t s_input_get_key_button_array_index(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return S_BUTTON_DEFAULT;
	}

	return s_input_key_buttons[index];
}

bool s_input_is_key_button_pressed(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_key_button_array_index(index) & S_BUTTON_PRESSED;
}

static bool s_input_has_key_button_changed(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_key_button_array_index(index) & S_BUTTON_CHANGED;
}

bool s_input_was_key_button_pressed(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return false;
	}

	return s_input_is_key_button_pressed(index) && s_input_has_key_button_changed(index);
}

bool s_input_was_key_button_released(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return false;
	}

	return !s_input_is_key_button_pressed(index) && s_input_has_key_button_changed(index);
}

void s_input_acknowledge_key_button(size_t index)
{
	if (index >= S_KEY_BUTTON_MAX)
	{
		return;
	}

	s_input_key_buttons[index] = (s_input_key_buttons[index] & S_BUTTON_PRESSED);
}

void s_input_acknowledge_all_key_buttons()
{
	for (size_t i = 0; i < S_KEY_BUTTON_MAX; ++i)
	{
		s_input_key_buttons[i] = (s_input_key_buttons[i] & S_BUTTON_PRESSED);
	}
}

void s_input_set_mouse_axis(float x, float y)
{
	s_input_mouse_axis.m_x = x;
	s_input_mouse_axis.m_y = y;
}

void s_input_get_mouse_axis(s_point_t* point)
{
	if (!point)
	{
		return;
	}

	point->m_x = s_input_mouse_axis.m_x;
	point->m_y = s_input_mouse_axis.m_y;
}

float s_input_get_mouse_axis_x()
{
	return s_input_mouse_axis.m_x;
}

float s_input_get_mouse_axis_y()
{
	return s_input_mouse_axis.m_y;
}

void s_input_set_mouse_button_array_index(size_t index, bool pressed)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return;
	}

	if (pressed)
	{
		s_input_mouse_buttons[index - ALLEGRO_MOUSE_BUTTON_LEFT] = (S_BUTTON_PRESSED | S_BUTTON_CHANGED);
	}
	else
	{
		s_input_mouse_buttons[index - ALLEGRO_MOUSE_BUTTON_LEFT] = S_BUTTON_CHANGED;
	}
}

uint8_t s_input_get_mouse_button_array_index(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return S_BUTTON_DEFAULT;
	}

	return s_input_mouse_buttons[index - ALLEGRO_MOUSE_BUTTON_LEFT];
}

bool s_input_is_mouse_button_pressed(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_mouse_button_array_index(index) & S_BUTTON_PRESSED;
}

static bool s_input_has_mouse_button_changed(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_mouse_button_array_index(index) & S_BUTTON_CHANGED;
}

bool s_input_was_mouse_button_pressed(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_is_mouse_button_pressed(index) && s_input_has_mouse_button_changed(index);
}

bool s_input_was_mouse_button_released(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return !s_input_is_mouse_button_pressed(index) && s_input_has_mouse_button_changed(index);
}

void s_input_acknowledge_mouse_button(size_t index)
{
	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_MOUSE_BUTTON_MAX)
	{
		return;
	}

	s_input_mouse_buttons[index - ALLEGRO_MOUSE_BUTTON_LEFT] = (s_input_mouse_buttons[index - ALLEGRO_MOUSE_BUTTON_LEFT] & S_BUTTON_PRESSED);
}

void s_input_acknowledge_all_mouse_buttons()
{
	for (size_t i = 0; i < S_MOUSE_BUTTON_MAX; ++i)
	{
		s_input_mouse_buttons[i] = (s_input_mouse_buttons[i] & S_BUTTON_PRESSED);
	}
}
