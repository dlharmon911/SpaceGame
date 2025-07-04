#ifndef _HEADER_GUARD_APPLICATION_H_
#define _HEADER_GUARD_APPLICATION_H_

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
	g_game_data_t m_game_data;
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_logic_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	S_INPUT_DATA* m_input_data;
	ALLEGRO_FONT* m_builtin_font;
	s_point_t m_display_scale;
	g_settings_t m_settings;
	bool m_update_logic;
	bool m_show_stats;
} g_app_data_t;

/// <summary>Zero initialize application data</summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a</returns>
void g_app_set_zero(g_app_data_t* data);

/// <summary>Initialize application</summary>
/// <param name='exe_name'> - Executable filename</param>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
int32_t g_app_initialize(const char* exe_filename, g_app_data_t* data);

/// <summary>Application is shut down. All data is freed in the process. </summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a - no return</returns>
void g_app_shutdown(g_app_data_t* data);

/// <summary>Application continues to loop until signaled to close. </summary>
/// <param name='data'> - pointer to container of application data</param>
/// <returns>n/a - no return</returns>
void g_app_loop(g_app_data_t* data);

#endif // !_HEADER_GUARD_APPLICATION_H_
