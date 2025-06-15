#ifndef _HEADER_GUARD_LIBSPACE_INPUT_H_
#define _HEADER_GUARD_LIBSPACE_INPUT_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

enum S_INPUT_INSTALL_FLAG
{
	S_INPUT_INSTALL_DEFAULT,
	S_INPUT_INSTALL_KEYBOARD = 0x01,
	S_INPUT_INSTALL_MOUSE = 0x02,
	S_INPUT_INSTALL_JOYSTICK = 0x04
};

typedef struct S_INPUT_DATA S_INPUT_DATA;

S_INPUT_DATA* s_input_install();
void s_input_uninstall(S_INPUT_DATA* data);
uint32_t s_input_get_install_flag(const S_INPUT_DATA* data);

void s_input_register_with_event_queue(const S_INPUT_DATA* data, ALLEGRO_EVENT_QUEUE* queue);
/// <summary>Sets the value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <param name="pressed">boolean value if pressed or not</param>
/// <returns>n/a - no return</returns>
void s_input_set_keyboard_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed);

/// <summary>Get a value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <returns>uint8_t - button state variable</returns>
uint8_t s_input_get_keyboard_button_array_index(const S_INPUT_DATA* data, size_t index);

/// <summary>Get button press status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button is currently being pressed</returns>
bool s_input_is_keyboard_button_pressed(const S_INPUT_DATA* data, size_t index);

/// <summary>Determine if button was pressed since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
/// 
bool s_input_was_keyboard_button_pressed(const S_INPUT_DATA* data, size_t index);
/// <summary>Determine if button was released since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_keyboard_button_released(const S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for individual button at index</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_keyboard_button(S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for all buttons</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_all_keyboard_buttons(S_INPUT_DATA* data);



/// <summary>Set the coordinates of the joystick axis</summary>
/// <param name="stick">stick index</param>
/// <param name="axis">axis index</param>
/// <param name="position">position (-1.0f to 1.0f)</param>
/// <returns>n/a</returns>
void s_input_set_joystick_axis(S_INPUT_DATA* data, int32_t stick, int32_t axis, float position);

/// <summary>Sets the value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <param name="pressed">boolean value if pressed or not</param>
/// <returns>n/a - no return</returns>
void s_input_set_joystick_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed);

/// <summary>Get a value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <returns>uint8_t - button state variable</returns>
uint8_t s_input_get_joystick_button_array_index(const S_INPUT_DATA* data, size_t index);

/// <summary>Get button press status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button is currently being pressed</returns>
bool s_input_is_joystick_button_pressed(const S_INPUT_DATA* data, size_t index);

/// <summary>Determine if button was pressed since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_joystick_button_pressed(const S_INPUT_DATA* data, size_t index);
/// <summary>Determine if button was released since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_joystick_button_released(const S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for individual button at index</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_joystick_button(S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for all buttons</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_all_joystick_buttons(S_INPUT_DATA* data);

/// <summary>Reconfigure if there joystick was unplugged/plugged in.</summary>
/// <param name="change">true if plugged in</param>
/// <returns>n/a</returns>
void s_input_reconfigure_joystick(S_INPUT_DATA* data, bool change);

/// <summary>Set the coordinates of the mouse axis</summary>
/// <param name="x">mouse horizontal position</param>
/// <param name="y">mouse vertical position</param>
/// <returns>n/a</returns>
void s_input_set_mouse_axis(S_INPUT_DATA* data, float x, float y);

/// <summary>Load the values of the mouse axis into a point struct</summary>
/// <param name="point">pointer to a point_t struct</param>
/// <returns>n/a</returns>
void s_input_get_mouse_axis(const S_INPUT_DATA* data, s_point_t* point);

/// <summary>Get x position of mouse axis</summary>
/// <param name="n/a"></param>
/// <returns>float - mouse x value</returns>
float s_input_get_mouse_axis_x(const S_INPUT_DATA* data);

/// <summary>Get x position of mouse axis</summary>
/// <param name="n/a"></param>
/// <returns>float - mouse x value</returns>
float s_input_get_mouse_axis_y(const S_INPUT_DATA* data);

/// <summary>Sets the value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <param name="pressed">boolean value if pressed or not</param>
/// <returns>n/a - no return</returns>
void s_input_set_mouse_button_array_index(S_INPUT_DATA* data, size_t index, bool pressed);

/// <summary>Get a value of the button state variable at index specified</summary>
/// <param name="index">index of button array</param>
/// <returns>uint8_t - button state variable</returns>
uint8_t s_input_get_mouse_button_array_index(const S_INPUT_DATA* data, size_t index);

/// <summary>Get button press status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button is currently being pressed</returns>
bool s_input_is_mouse_button_pressed(const S_INPUT_DATA* data, size_t index);

/// <summary>Determine if button was pressed since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_mouse_button_pressed(const S_INPUT_DATA* data, size_t index);

/// <summary>Determine if button was released since last checked status</summary>
/// <param name="index">index of button array</param>
/// <returns>bool - true if button has been pressed</returns>
bool s_input_was_mouse_button_released(const S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for individual button at index</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_mouse_button(S_INPUT_DATA* data, size_t index);

/// <summary>Resets the internal value of was_pressed/was_released for all buttons</summary>
/// <param name="index">index of button array</param>
/// <returns>n/a</returns>
void s_input_acknowledge_all_mouse_buttons(S_INPUT_DATA* data);

#endif // !_HEADER_GUARD_LIBSPACE_INPUT_H_
