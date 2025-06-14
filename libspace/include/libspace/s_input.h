#ifndef _HEADER_GUARD_LIBSPACE_INPUT_H_
#define _HEADER_GUARD_LIBSPACE_INPUT_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum
{
	S_KEY_BUTTON_MAX = ALLEGRO_KEY_MAX,
	S_MOUSE_BUTTON_MAX = ALLEGRO_MOUSE_BUTTON_MIDDLE
};

/// <summary>Sets the value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <param name="pressed">boolean value if pressed or not</param>
/// <returns>n/a - no return</returns>
void s_input_set_key_button_array_index(size_t index, bool pressed);

/// <summary>Get a value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <returns>uint8_t - button state variable</returns>
uint8_t s_input_get_key_button_array_index(size_t index);

/// <summary>Get button press status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button is currently being pressed</returns>
bool s_input_is_key_button_pressed(size_t index);

/// <summary>Determine if button was pressed since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_key_button_pressed(size_t index);
/// <summary>Determine if button was released since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_key_button_released(size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for individual button at index</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_key_button(size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for all buttons</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_all_key_buttons();

/// <summary>Set the coordinates of the mouse axis</summary>
/// <param name="x">mouse horizontal position</param>
/// <param name="y">mouse vertical position</param>
/// <returns>n/a</returns>
void s_input_set_mouse_axis(float x, float y);

/// <summary>Load the values of the mouse axis into a point struct</summary>
/// <param name="point">pointer to a point_t struct</param>
/// <returns>n/a</returns>
void s_input_get_mouse_axis(s_point_t* point);

/// <summary>Get x position of mouse axis</summary>
/// <param name="n/a"></param>
/// <returns>float - mouse x value</returns>
float s_input_get_mouse_axis_x();

/// <summary>Get x position of mouse axis</summary>
/// <param name="n/a"></param>
/// <returns>float - mouse x value</returns>
float s_input_get_mouse_axis_y();

/// <summary>Sets the value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <param name="pressed">boolean value if pressed or not</param>
/// <returns>n/a - no return</returns>
void s_input_set_mouse_button_array_index(size_t index, bool pressed);

/// <summary>Get a value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <returns>uint8_t - button state variable</returns>
uint8_t s_input_get_mouse_button_array_index(size_t index);

/// <summary>Get button press status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button is currently being pressed</returns>
bool s_input_is_mouse_button_pressed(size_t index);

/// <summary>Determine if button was pressed since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_mouse_button_pressed(size_t index);
/// <summary>Determine if button was released since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_mouse_button_released(size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for individual button at index</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_mouse_button(size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for all buttons</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_all_mouse_buttons();

#endif // !_HEADER_GUARD_LIBSPACE_INPUT_H_
