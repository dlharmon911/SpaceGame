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

void g_app_zero_initialize_data(g_app_data_t* data)
{
	if (!data)
	{
		return;
	}

	data->m_display = NULL;
	data->m_logic_timer = NULL;
	data->m_event_queue = NULL;
	data->m_input_data = NULL;
	data->m_builtin_font = NULL;
	data->m_update_logic = false;
	data->m_show_stats = false;
	s_point_set_f(&data->m_display_scale, 1.0f, 1.0f);
	g_game_zero_initialize_data(&data->m_game_data);
	s_viewport_zero_initialize_data(&data->m_viewport);

	s_point_set_f(&data->m_viewport.m_size, 600.0f, 600.0f);
	s_point_set_f(&data->m_viewport.m_point,
		(G_DISPLAY_INITIAL_SIZE.m_x - data->m_viewport.m_size.m_x) * 0.5f,
		(G_DISPLAY_INITIAL_SIZE.m_y - data->m_viewport.m_size.m_y) * 0.5f);
}

int32_t g_app_initialize(int32_t argc, char** argv, g_app_data_t* data)
{
	if (!argv)
	{
		return -1;
	}

	if (!data)
	{
		return -1;
	}

	if (!al_init())
	{
		return -1;
	}

	s_random_set_seed((uint32_t)time(NULL));

	s_log_open("output.txt");
	if (!s_log_is_open())
	{
		return -1;
	}
	s_log_println("Initialization begin");

	s_log_print("Loading config settings - ");
	if (g_settings_load("config.ini", &data->m_settings) < 0)
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Initializing Image Addon- ");
	if (!al_init_image_addon())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Initializing Primitives Addon- ");
	if (!al_init_primitives_addon())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Initializing Font Addon- ");
	if (!al_init_font_addon())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Initializing PhysicsFS Addon- ");
	if (!PHYSFS_init(argv[0]))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Installing the input - ");
	if (!(data->m_input_data = s_input_install()))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_printf("Creating the display (%.1lf, %.1lf) - ", data->m_settings.m_display.m_size.m_x, data->m_settings.m_display.m_size.m_y);

	al_set_new_window_title(G_TITLE);
	al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
	if (!(data->m_display = al_create_display((int32_t)data->m_settings.m_display.m_size.m_x, (int32_t)data->m_settings.m_display.m_size.m_y)))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");
	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);
	al_flip_display();
	s_point_set_f(&data->m_display_scale,
		(data->m_settings.m_display.m_size.m_x / G_DISPLAY_INITIAL_SIZE.m_x),
		(data->m_settings.m_display.m_size.m_y / G_DISPLAY_INITIAL_SIZE.m_y));

	s_log_printf("Creating the timer (%.1lf) - ", 1.0 / G_LOGIC_TIMER_RATE);
	if (!(data->m_logic_timer = al_create_timer(1.0 / G_LOGIC_TIMER_RATE)))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Creating the event queue - ");
	if (!(data->m_event_queue = al_create_event_queue()))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	al_register_event_source(data->m_event_queue, al_get_display_event_source(data->m_display));
	al_register_event_source(data->m_event_queue, al_get_timer_event_source(data->m_logic_timer));
	s_input_register_with_event_queue(data->m_input_data, data->m_event_queue);

	s_log_print("Creating the built-in font - ");
	if (!(data->m_builtin_font = al_create_builtin_font()))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	if (g_game_initialize_data(&data->m_game_data) < 0)
	{
		return -1;
	}

	s_log_println("Initialization end\n");
	s_log_flush();

	data->m_game_data.m_input_data = data->m_input_data;
	data->m_game_data.m_is_running = true;
	data->m_game_data.m_settings = &data->m_settings;
	data->m_game_data.m_stats.m_settings = &data->m_settings;

	return 0;
}

void g_app_shutdown(g_app_data_t* data)
{
	if (!data)
	{
		return;
	}

	s_log_println("Shutdown begin");

	g_game_destroy_data(&data->m_game_data);

	if (data->m_builtin_font)
	{
		al_destroy_font(data->m_builtin_font);
		data->m_builtin_font = NULL;
		s_log_println("The built-in font has been destroyed");
	}

	if (data->m_event_queue)
	{
		al_destroy_event_queue(data->m_event_queue);
		data->m_event_queue = NULL;
		s_log_println("The event queue has been destroyed");
	}

	if (data->m_logic_timer)
	{
		al_destroy_timer(data->m_logic_timer);
		data->m_logic_timer = NULL;
		s_log_println("The timer has been destroyed");
	}

	if (data->m_display)
	{
		al_destroy_display(data->m_display);
		data->m_display = NULL;
		s_log_println("The display has been destroyed");
	}

	if (data->m_input_data)
	{
		s_input_uninstall(data->m_input_data);
		s_log_println("Input has been uninstalled");
		data->m_input_data = NULL;
	}

	if (PHYSFS_isInit())
	{
		PHYSFS_deinit();
	}

	if (al_is_font_addon_initialized())
	{
		s_log_println("Uninitializing font addon");
		al_shutdown_font_addon();
	}

	if (al_is_primitives_addon_initialized())
	{
		s_log_println("Uninitializing primitives addon");
		al_shutdown_primitives_addon();
	}

	if (al_is_image_addon_initialized())
	{
		s_log_println("Uninitializing image addon");
		al_shutdown_image_addon();
	}

	s_log_print("Saving settings to config file - ");
	if (g_settings_save("config.ini", &data->m_settings) < 0)
	{
		s_log_println("failed");
	}
	else
	{
		s_log_println("success");
	}

	s_log_println("Shutdown end");

	s_log_flush();
	s_log_close();

	if (al_is_system_installed())
	{
		al_uninstall_system();
	}
}

/// <summary>Processes all events in the event queue.</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_input(g_app_data_t* data)
{
	ALLEGRO_EVENT event;

	if (!data)
	{
		return;
	}

	while (!al_is_event_queue_empty(data->m_event_queue))
	{
		al_get_next_event(data->m_event_queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
		{
			data->m_update_logic = true;
		} break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			data->m_game_data.m_is_running = false;
		} break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
		{
			data->m_settings.m_display.m_size.m_x = (float)event.display.width;
			data->m_settings.m_display.m_size.m_y = (float)event.display.height;
			s_point_set_f(&data->m_display_scale,
				(data->m_settings.m_display.m_size.m_x / G_DISPLAY_INITIAL_SIZE.m_x),
				(data->m_settings.m_display.m_size.m_y / G_DISPLAY_INITIAL_SIZE.m_y));

			al_acknowledge_resize(event.display.source);
		} break;
		case ALLEGRO_EVENT_KEY_DOWN:
		{
			s_input_set_keyboard_button_array_index(data->m_input_data, (size_t)event.keyboard.keycode, true);
		} break;
		case ALLEGRO_EVENT_KEY_UP:
		{
			s_input_set_keyboard_button_array_index(data->m_input_data, (size_t)event.keyboard.keycode, false);
		} break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			s_input_set_mouse_axis(data->m_input_data, (float)event.mouse.x, (float)event.mouse.y);
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			s_input_set_mouse_button_array_index(data->m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			s_input_set_mouse_button_array_index(data->m_input_data, (size_t)event.mouse.button, false);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
		{
			s_input_set_joystick_axis(data->m_input_data, event.joystick.stick, event.joystick.axis, event.joystick.pos);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
		{
			s_input_set_joystick_button_array_index(data->m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
		{
			s_input_set_joystick_button_array_index(data->m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
		{
			s_input_reconfigure_joystick(data->m_input_data, al_reconfigure_joysticks());
		} break;
		default: return;
		}
	}
}

/// <summary>Logic for the application is processed. </summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_logic(g_app_data_t* data)
{
	if (!data)
	{
		return;
	}

	if (s_input_was_keyboard_button_released(data->m_input_data, ALLEGRO_KEY_F1))
	{
		data->m_show_stats = !data->m_show_stats;
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_F1);
	}

	if (s_input_was_keyboard_button_released(data->m_input_data, ALLEGRO_KEY_F2))
	{
		s_screenshot_save(al_get_backbuffer(data->m_display));
		s_input_acknowledge_keyboard_button(data->m_input_data, ALLEGRO_KEY_F2);
	}

	g_game_logic(&data->m_game_data);
}

static void g_app_draw_view(const g_app_data_t* data, const s_viewport_t* viewport)
{
	if (!data)
	{
		return;
	}

	if (!viewport)
	{
		return;
	}

	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;
	static int32_t clip[4] = { 0, 0, 0, 0 };

	al_get_clipping_rectangle(clip, clip + 1, clip + 2, clip + 3);
	al_set_clipping_rectangle((int32_t)(viewport->m_point.m_x * data->m_display_scale.m_x),
		(int32_t)(viewport->m_point.m_y * data->m_display_scale.m_y),
		(int32_t)(viewport->m_size.m_x * data->m_display_scale.m_x),
		(int32_t)(viewport->m_size.m_y * data->m_display_scale.m_y));

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_scale_transform(&transform, 1.0f, -1.0f);
	al_translate_transform(&transform, viewport->m_point.m_x + viewport->m_size.m_x * 0.5f, viewport->m_point.m_y + viewport->m_size.m_y * 0.5f);
	al_scale_transform(&transform, data->m_display_scale.m_x, data->m_display_scale.m_y);
	al_compose_transform(&transform, &backup);
	al_use_transform(&transform);

	g_game_draw(&data->m_game_data, viewport);

	al_use_transform(&backup);
	al_set_clipping_rectangle(clip[0], clip[1], clip[2], clip[3]);
}

/// <summary>Display is updated. The double buffer is set as the target bitmap. After it is drawn to, the display
/// gets set as the target bitmap. Then the double buffer is drawn to display.</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_draw(const g_app_data_t* data)
{
	if (!data)
	{
		return;
	}
	
	static ALLEGRO_TRANSFORM backup;
	static ALLEGRO_TRANSFORM transform;

	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);
	g_app_draw_view(data, &data->m_viewport);

	al_copy_transform(&backup, al_get_current_transform());
	al_identity_transform(&transform);
	al_scale_transform(&transform, 1.0f, 2.0f);
	al_use_transform(&transform);

	if (data->m_show_stats)
	{
		g_stats_draw(data->m_builtin_font, &data->m_game_data.m_stats, 0.0f, 0.0f);
	}

	al_use_transform(&backup);

	al_flip_display();
}

void g_app_loop(g_app_data_t* data)
{
	double start_time = 0.0;
	double end_time = 0.0;

	if (!data)
	{
		return;
	}

	al_start_timer(data->m_logic_timer);

	while (data->m_game_data.m_is_running)
	{
		g_app_input(data);

		if (data->m_update_logic)
		{
			data->m_update_logic = false;
			g_app_logic(data);
		}

		g_app_draw(data);

		end_time = al_get_time();
		data->m_game_data.m_stats.m_fps = (float)(1.0 / (end_time - start_time));
		start_time = end_time;
	}

	al_stop_timer(data->m_logic_timer);
}
