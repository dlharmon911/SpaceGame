#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "g_constants.h"
#include "g_app.h"
#include "g_game.h"

typedef struct g_app_data_t
{
	g_game_data_t m_game_data;
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_logic_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	S_INPUT_DATA* m_input_data;
	bool m_update_logic;
} g_app_data_t;

static g_app_data_t g_data;

static void g_app_set_zero()
{
	g_data.m_display = NULL;
	g_data.m_logic_timer = NULL;
	g_data.m_event_queue = NULL;
	g_data.m_update_logic = false;

	g_game_set_zero(&g_data.m_game_data);
}

int32_t g_app_initialize()
{
	g_app_set_zero();

	if (!al_init())
	{
		return -1;
	}

	s_log_open("output.txt");
	if (!s_log_is_open())
	{
		return -1;
	}
	s_log_println("Initialization begin");

	s_log_print("Initializing Font Addon- ");
	if (!al_init_font_addon())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Installing the input - ");
	if (!(g_data.m_input_data = s_input_install()))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_printf("Creating the display (%.1lf, %.1lf) - ", G_DISPLAY_INITIAL_SIZE.m_x, G_DISPLAY_INITIAL_SIZE.m_y);

	al_set_new_window_title(G_TITLE);
	if (!(g_data.m_display = al_create_display((int32_t)G_DISPLAY_INITIAL_SIZE.m_x, (int32_t)G_DISPLAY_INITIAL_SIZE.m_y)))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");
	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);
	al_flip_display();

	s_log_printf("Creating the timer (%.1lf) - ", 1.0 / G_LOGIC_TIMER_RATE);
	if (!(g_data.m_logic_timer = al_create_timer(1.0 / G_LOGIC_TIMER_RATE)))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Creating the event queue - ");
	if (!(g_data.m_event_queue = al_create_event_queue()))
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	al_register_event_source(g_data.m_event_queue, al_get_display_event_source(g_data.m_display));
	al_register_event_source(g_data.m_event_queue, al_get_timer_event_source(g_data.m_logic_timer));
	s_input_register_with_event_queue(g_data.m_input_data, g_data.m_event_queue);

	s_log_println("Initialization end\n");
	s_log_flush();

	g_data.m_game_data.m_is_running = true;
	g_data.m_game_data.m_input_data = g_data.m_input_data;

	return 0;
}

void g_app_shutdown()
{
	s_log_println("Shutdown begin");

	if (g_data.m_event_queue)
	{
		al_destroy_event_queue(g_data.m_event_queue);
		g_data.m_event_queue = NULL;
		s_log_println("The event queue has been destroyed");
	}

	if (g_data.m_logic_timer)
	{
		al_destroy_timer(g_data.m_logic_timer);
		g_data.m_logic_timer = NULL;
		s_log_println("The timer has been destroyed");
	}

	if (g_data.m_display)
	{
		al_destroy_display(g_data.m_display);
		g_data.m_display = NULL;
		s_log_println("The display has been destroyed");
	}

	if (g_data.m_input_data)
	{
		s_input_uninstall(g_data.m_input_data);
		s_log_println("Input has been uninstalled");
		g_data.m_input_data = NULL;
	}

	if (al_is_font_addon_initialized())
	{
		al_shutdown_font_addon();
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
static void g_app_input()
{
	ALLEGRO_EVENT event;

	while (!al_is_event_queue_empty(g_data.m_event_queue))
	{
		al_get_next_event(g_data.m_event_queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
		{
			g_data.m_update_logic = true;
		} break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			g_data.m_game_data.m_is_running = false;
		} break;
		case ALLEGRO_EVENT_KEY_DOWN:
		{
			s_input_set_keyboard_button_array_index(g_data.m_input_data, (size_t)event.keyboard.keycode, true);
		} break;
		case ALLEGRO_EVENT_KEY_UP:
		{
			s_input_set_keyboard_button_array_index(g_data.m_input_data, (size_t)event.keyboard.keycode, false);
		} break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		{
			s_input_set_mouse_axis(g_data.m_input_data, (float)event.mouse.x, (float)event.mouse.y);
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		{
			s_input_set_mouse_button_array_index(g_data.m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		{
			s_input_set_mouse_button_array_index(g_data.m_input_data, (size_t)event.mouse.button, false);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
		{
			s_input_set_joystick_axis(g_data.m_input_data, event.joystick.stick, event.joystick.axis, event.joystick.pos);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
		{
			s_input_set_joystick_button_array_index(g_data.m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
		{
			s_input_set_joystick_button_array_index(g_data.m_input_data, (size_t)event.mouse.button, true);
		} break;
		case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
		{
			s_input_reconfigure_joystick(g_data.m_input_data, al_reconfigure_joysticks());
		} break;
		default: return;
		}
	}
}

/// <summary>Logic for the application is processed. </summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_logic()
{
	g_game_logic();
}

/// <summary>Display is updated. The double buffer is set as the target bitmap. After it is drawn to, the display
/// gets set as the target bitmap. Then the double buffer is drawn to display.</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_draw()
{
	g_game_draw();
	al_flip_display();
}

void g_app_loop()
{
	al_start_timer(g_data.m_logic_timer);

	while (g_data.m_game_data.m_is_running)
	{
		g_app_input();

		if (g_data.m_update_logic)
		{
			g_data.m_update_logic = false;
			g_app_logic();
		}

		g_app_draw();
	}

	al_stop_timer(g_data.m_logic_timer);
}
