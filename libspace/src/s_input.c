#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_input.h"

enum S_INPUT_BUTTON_COUNT
{
	S_INPUT_KEYBOARD_BUTTON_MAX = ALLEGRO_KEY_MAX,
	S_INPUT_MOUSE_BUTTON_MAX = ALLEGRO_MOUSE_BUTTON_MIDDLE,
	S_INPUT_JOYSTICK_AXES_MAX = 3,
	S_INPUT_JOYSTICK_STICK_MAX = 16,
	S_INPUT_JOYSTICK_BUTTON_MAX = 36
};

enum S_INPUT_BUTTON_FLAG
{
	S_INPUT_BUTTON_DEFAULT,
	S_INPUT_BUTTON_PRESSED = 0x01,
	S_INPUT_BUTTON_CHANGED = 0x02
};

typedef struct S_INPUT_JOYSTICK_STICK
{
	float axis[S_INPUT_JOYSTICK_AXES_MAX];
} S_INPUT_JOYSTICK_STICK;

typedef struct S_INPUT_JOYSTICK_STATE
{
	S_INPUT_JOYSTICK_STICK m_stick[S_INPUT_JOYSTICK_STICK_MAX];
	uint8_t m_button[S_INPUT_JOYSTICK_BUTTON_MAX];
} S_INPUT_JOYSTICK_STATE;

typedef struct S_INPUT_MOUSE_DATA
{
	s_point_t m_axis;
	uint8_t m_button[S_INPUT_MOUSE_BUTTON_MAX];
	uint32_t m_install_flag;
} S_INPUT_MOUSE_DATA;

typedef struct S_INPUT_KEYBOARD_DATA
{
	uint8_t m_button[S_INPUT_KEYBOARD_BUTTON_MAX];
	uint32_t m_install_flag;
} S_INPUT_KEYBOARD_DATA;

typedef struct S_INPUT_JOYSTICK_DATA
{
	ALLEGRO_JOYSTICK* m_joystick;
	S_INPUT_JOYSTICK_STATE m_state;
	uint32_t m_install_flag;
} S_INPUT_JOYSTICK_DATA;

typedef struct S_INPUT_DATA
{
	S_INPUT_MOUSE_DATA m_mouse;
	S_INPUT_KEYBOARD_DATA m_keyboard;
	S_INPUT_JOYSTICK_DATA m_joystick;
} S_INPUT_DATA;

static void s_input_mouse_zero_initialize_data(S_INPUT_MOUSE_DATA* data)
{
	if (!data)
	{
		return;
	}

	for (size_t i = 0; i < S_INPUT_MOUSE_BUTTON_MAX; ++i)
	{
		data->m_button[i] = 0;
	}
	s_point_zero_initialize_data(&data->m_axis);
	data->m_install_flag = S_INPUT_INSTALL_DEFAULT;
}

static void s_input_keyboard_zero_initialize_data(S_INPUT_KEYBOARD_DATA* data)
{
	if (!data)
	{
		return;
	}

	for (size_t i = 0; i < S_INPUT_KEYBOARD_BUTTON_MAX; ++i)
	{
		data->m_button[i] = 0;
	}
	data->m_install_flag = S_INPUT_INSTALL_DEFAULT;
}

static void s_input_joystick_zero_initialize_data(S_INPUT_JOYSTICK_DATA* data)
{
	if (!data)
	{
		return;
	}

	data->m_joystick = NULL;	
	
	for (size_t i = 0; i < S_INPUT_JOYSTICK_STICK_MAX; ++i)
	{
		S_INPUT_JOYSTICK_STICK* stick = &data->m_state.m_stick[i];
		for (size_t j = 0; j < S_INPUT_JOYSTICK_AXES_MAX; ++j)
		{
			stick->axis[j] = 0.0f;
		}
	}

	for (size_t i = 0; i < S_INPUT_JOYSTICK_BUTTON_MAX; ++i)
	{
		data->m_state.m_button[i] = 0;
	}
	data->m_install_flag = S_INPUT_INSTALL_DEFAULT;

}

static void s_input_zero_initialize_data(S_INPUT_DATA* data)
{
	if (!data)
	{
		return;
	}

	s_input_mouse_zero_initialize_data(&data->m_mouse);
	s_input_keyboard_zero_initialize_data(&data->m_keyboard);
	s_input_joystick_zero_initialize_data(&data->m_joystick);
}

static int32_t s_input_install_mouse_data(S_INPUT_MOUSE_DATA* data)
{
	if (!data)
	{
		return -1;
	}

	if (data->m_install_flag)
	{
		return -1;
	}
	
	if (!al_install_mouse())
	{
		return -1;
	}

	data->m_install_flag = S_INPUT_INSTALL_MOUSE;

	return 0;
}

static int32_t s_input_install_keyboard_data(S_INPUT_KEYBOARD_DATA* data)
{
	if (!data)
	{
		return -1;
	}

	if (data->m_install_flag)
	{
		return -1;
	}

	if (!al_install_keyboard())
	{
		return -1;
	}

	data->m_install_flag = S_INPUT_INSTALL_KEYBOARD;

	return 0;
}

static void s_input_install_joystick_data(S_INPUT_JOYSTICK_DATA* data)
{
	if (!data)
	{
		return;
	}

	if (data->m_install_flag)
	{
		return;
	}

	if (!al_install_joystick())
	{
		return;
	}
	
	data->m_joystick = al_get_joystick(0);
	data->m_install_flag = S_INPUT_INSTALL_JOYSTICK;
}

static int32_t s_input_install_data(S_INPUT_DATA** data)
{
	if (!data)
	{
		return -1;
	}

	if (*data)
	{
		return -1;
	}

	(*data) = (S_INPUT_DATA*)al_malloc(sizeof(S_INPUT_DATA));

	if (!(*data))
	{
		return -1;
	}

	s_input_zero_initialize_data(*data);

	if (s_input_install_mouse_data(&(*data)->m_mouse) < 0)
	{
		return -1;
	}

	if (s_input_install_keyboard_data(&(*data)->m_keyboard) < 0)
	{
		return -1;
	}

	s_input_install_joystick_data(&(*data)->m_joystick);

	return 0;
}

S_INPUT_DATA* s_input_install()
{
	S_INPUT_DATA* data = NULL;

	if (s_input_install_data(&data) < 0)
	{
		s_input_uninstall(data);
		data = NULL;
	}

	return data;
}

void s_input_uninstall(S_INPUT_DATA* data)
{
	if (!data)
	{
		return;
	}

	if (data->m_mouse.m_install_flag)
	{
		al_uninstall_mouse();
		data->m_mouse.m_install_flag = S_INPUT_INSTALL_DEFAULT;
	}

	if (data->m_keyboard.m_install_flag)
	{
		al_uninstall_keyboard();
		data->m_keyboard.m_install_flag = S_INPUT_INSTALL_DEFAULT;
	}

	if (data->m_joystick.m_install_flag)
	{
		al_uninstall_joystick();
		data->m_joystick.m_install_flag = S_INPUT_INSTALL_DEFAULT;
	}

	al_free(data);
}

uint32_t s_input_get_install_flag(const S_INPUT_DATA* data)
{
	if (!data)
	{
		return 0;
	}

	return (data->m_keyboard.m_install_flag |
			data->m_mouse.m_install_flag |
			data->m_joystick.m_install_flag);
}

void s_input_register_with_event_queue(const S_INPUT_DATA* data, ALLEGRO_EVENT_QUEUE* queue)
{
	if (!data)
	{
		return;
	}

	if (!queue)
	{
		return;
	}

	if (data->m_mouse.m_install_flag)
	{
		al_register_event_source(queue, al_get_mouse_event_source());
	}

	if (data->m_keyboard.m_install_flag)
	{
		al_register_event_source(queue, al_get_keyboard_event_source());
	}

	if (data->m_joystick.m_install_flag)
	{
		al_register_event_source(queue, al_get_joystick_event_source());
	}
}

void s_input_set_keyboard_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed)
{
	if (!data)
	{
		return;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return;
	}

	if (pressed)
	{
		data->m_keyboard.m_button[index] = (S_INPUT_BUTTON_PRESSED | S_INPUT_BUTTON_CHANGED);
	}
	else
	{
		data->m_keyboard.m_button[index] = S_INPUT_BUTTON_CHANGED;
	}
}

uint8_t s_input_get_keyboard_button_array_index(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return 0;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return S_INPUT_BUTTON_DEFAULT;
	}

	return data->m_keyboard.m_button[index];
}

bool s_input_is_keyboard_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_keyboard_button_array_index(data, index) & S_INPUT_BUTTON_PRESSED;
}

static bool s_input_has_keyboard_button_changed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_keyboard_button_array_index(data, index) & S_INPUT_BUTTON_CHANGED;
}

bool s_input_was_keyboard_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return false;
	}

	return s_input_is_keyboard_button_pressed(data, index) && s_input_has_keyboard_button_changed(data, index);
}

bool s_input_was_keyboard_button_released(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return false;
	}

	return !s_input_is_keyboard_button_pressed(data, index) && s_input_has_keyboard_button_changed(data, index);
}

void s_input_acknowledge_keyboard_button(S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return;
	}

	if (index >= S_INPUT_KEYBOARD_BUTTON_MAX)
	{
		return;
	}

	data->m_keyboard.m_button[index] = (data->m_keyboard.m_button[index] & S_INPUT_BUTTON_PRESSED);
}

void s_input_acknowledge_all_keyboard_buttons(S_INPUT_DATA* data)
{
	if (!data)
	{
		return;
	}

	for (size_t i = 0; i < S_INPUT_KEYBOARD_BUTTON_MAX; ++i)
	{
		data->m_keyboard.m_button[i] = (data->m_keyboard.m_button[i] & S_INPUT_BUTTON_PRESSED);
	}
}

void s_input_set_joystick_axis(S_INPUT_DATA* data, int32_t stick, int32_t axis, float position)
{
	if (!data)
	{
		return;
	}

	if (stick >= al_get_joystick_num_sticks(data->m_joystick.m_joystick))
	{
		return;
	}

	if (axis >= al_get_joystick_num_axes(data->m_joystick.m_joystick, stick))
	{
		return;
	}

	data->m_joystick.m_state.m_stick[stick].axis[axis] = position;
}


void s_input_set_joystick_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed)
{
	if (!data)
	{
		return;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return;
	}

	if (pressed)
	{
		data->m_joystick.m_state.m_button[index] = (S_INPUT_BUTTON_PRESSED | S_INPUT_BUTTON_CHANGED);
	}
	else
	{
		data->m_joystick.m_state.m_button[index] = S_INPUT_BUTTON_CHANGED;
	}
}

uint8_t s_input_get_joystick_button_array_index(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return 0;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return 0;
	}

	return data->m_joystick.m_state.m_button[index];
}

bool s_input_is_joystick_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return false;
	}

	return s_input_get_joystick_button_array_index(data, index) & S_INPUT_BUTTON_PRESSED;
}

static bool s_input_has_joystick_button_changed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return false;
	}

	return s_input_get_joystick_button_array_index(data, index) & S_INPUT_BUTTON_CHANGED;
}

bool s_input_was_joystick_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return false;
	}

	return s_input_is_joystick_button_pressed(data, index) && s_input_has_joystick_button_changed(data, index);
}

bool s_input_was_joystick_button_released(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return false;
	}

	return !s_input_is_joystick_button_pressed(data, index) && s_input_has_joystick_button_changed(data, index);
}

void s_input_acknowledge_joystick_button(S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return;
	}

	if (index >= al_get_joystick_num_buttons(data->m_joystick.m_joystick))
	{
		return;
	}

	data->m_joystick.m_state.m_button[index] = (data->m_joystick.m_state.m_button[index] & S_INPUT_BUTTON_PRESSED);
}

void s_input_acknowledge_all_joystick_buttons(S_INPUT_DATA* data)
{
	if (!data)
	{
		return;
	}

	for (size_t i = 0; i < al_get_joystick_num_buttons(data->m_joystick.m_joystick); ++i)
	{
		data->m_joystick.m_state.m_button[i] = (data->m_joystick.m_state.m_button[i] & S_INPUT_BUTTON_PRESSED);
	}
}

void s_input_reconfigure_joystick(S_INPUT_DATA* data, bool change)
{
	if (change)
	{
		s_input_joystick_zero_initialize_data(&data->m_joystick);
	}
}

void s_input_set_mouse_axis(S_INPUT_DATA* data, float x, float y)
{
	if (!data)
	{
		return;
	}

	data->m_mouse.m_axis.m_x = x;
	data->m_mouse.m_axis.m_y = y;
}

void s_input_get_mouse_axis(const S_INPUT_DATA* data, s_point_t* point)
{
	if (!data)
	{
		return;
	}

	if (!point)
	{
		return;
	}

	point->m_x = data->m_mouse.m_axis.m_x;
	point->m_y = data->m_mouse.m_axis.m_y;
}

float s_input_get_mouse_axis_x(const S_INPUT_DATA* data)
{
	if (!data)
	{
		return 0.0f;
	}

	return data->m_mouse.m_axis.m_x;
}

float s_input_get_mouse_axis_y(const S_INPUT_DATA* data)
{
	if (!data)
	{
		return 0.0f;
	}

	return data->m_mouse.m_axis.m_y;
}

void s_input_set_mouse_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed)
{
	if (!data)
	{
		return;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return;
	}

	if (pressed)
	{
		data->m_mouse.m_button[index - ALLEGRO_MOUSE_BUTTON_LEFT] = (S_INPUT_BUTTON_PRESSED | S_INPUT_BUTTON_CHANGED);
	}
	else
	{
		data->m_mouse.m_button[index - ALLEGRO_MOUSE_BUTTON_LEFT] = S_INPUT_BUTTON_CHANGED;
	}
}

uint8_t s_input_get_mouse_button_array_index(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return 0;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return S_INPUT_BUTTON_DEFAULT;
	}

	return data->m_mouse.m_button[index - ALLEGRO_MOUSE_BUTTON_LEFT];
}

bool s_input_is_mouse_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_mouse_button_array_index(data, index) & S_INPUT_BUTTON_PRESSED;
}

static bool s_input_has_mouse_button_changed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_get_mouse_button_array_index(data, index) & S_INPUT_BUTTON_CHANGED;
}

bool s_input_was_mouse_button_pressed(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return s_input_is_mouse_button_pressed(data, index) && s_input_has_mouse_button_changed(data, index);
}

bool s_input_was_mouse_button_released(const S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return false;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return false;
	}

	return !s_input_is_mouse_button_pressed(data, index) && s_input_has_mouse_button_changed(data, index);
}

void s_input_acknowledge_mouse_button(S_INPUT_DATA* data, size_t index)
{
	if (!data)
	{
		return;
	}

	if (index < ALLEGRO_MOUSE_BUTTON_LEFT || index >= S_INPUT_MOUSE_BUTTON_MAX)
	{
		return;
	}

	data->m_mouse.m_button[index - ALLEGRO_MOUSE_BUTTON_LEFT] = (data->m_mouse.m_button[index - ALLEGRO_MOUSE_BUTTON_LEFT] & S_INPUT_BUTTON_PRESSED);
}

void s_input_acknowledge_all_mouse_buttons(S_INPUT_DATA* data)
{
	if (!data)
	{
		return;
	}

	for (size_t i = 0; i < S_INPUT_MOUSE_BUTTON_MAX; ++i)
	{
		data->m_mouse.m_button[i] = (data->m_mouse.m_button[i] & S_INPUT_BUTTON_PRESSED);
	}
}
