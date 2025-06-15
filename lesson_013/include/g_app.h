#ifndef _HEADER_GUARD_APPLICATION_H_
#define _HEADER_GUARD_APPLICATION_H_

/*     _____                        _____
 *    /  ___|                      |  __ \
 *    \ `--. _ __   __ _  ___ ___  | |  \/ __ _ _ __ ___   ___
 *     `--. \ '_ \ / _` |/ __/ _ \ | | __ / _` | '_ ` _ \ / _ \
 *    /\__/ / |_) | (_| | (_|  __/ | |_\ \ (_| | | | | | |  __/
 *    \____/| .__/ \__,_|\___\___|  \____/\__,_|_| |_| |_|\___|
 *          | |
 *          |_|
 *
 *      By Daniel Harmon.
 */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include <time.h>
#include "g_constants.h"
#include "g_app.h"
#include "g_game.h"

/// <summary>Data struct for application</summary>
typedef struct g_app_data_t
{
	/// <summary>Data struct for game specific</summary>
	g_game_data_t m_game_data;
	/// <summary>Display member</summary>
	ALLEGRO_DISPLAY* m_display;
	/// <summary>Logic timer member</summary>
	ALLEGRO_TIMER* m_logic_timer;
	/// <summary>Event Queue member</summary>
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	/// <summary>Input data (keyboard, mouse, joystick)</summary>
	S_INPUT_DATA* m_input_data;
	/// <summary>Font used to display stats</summary>
	ALLEGRO_FONT* m_builtin_font;
	/// <summary>Scale ration of display to actual game area</summary>
	s_point_t m_display_scale;
	/// <summary>Data struct for configuration settings</summary>
	g_settings_t m_settings;
	/// <summary>Boolean to update logic if set to true</summary>
	bool m_update_logic;
	/// <summary>Boolean to show statistics if set to true</summary>
	bool m_show_stats;
} g_app_data_t;

/// <summary>Zero initialize application data</summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a</returns>
void g_app_zero_initialize_data(g_app_data_t* data);

/// <summary>Initialize application</summary>
/// <param name='argc'> - argument array size passed from main</param>
/// <param name='argv'> - argument array passed from main</param>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
int32_t g_app_initialize(int32_t argc, char** argv, g_app_data_t* data);

/// <summary>Application is shut down. All data is freed in the process. </summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a - no return</returns>
void g_app_shutdown(g_app_data_t* data);

/// <summary>Application continues to loop until signaled to close. </summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a - no return</returns>
void g_app_loop(g_app_data_t* data);

#endif // !_HEADER_GUARD_APPLICATION_H_
