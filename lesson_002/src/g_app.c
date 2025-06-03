#include <allegro5/allegro5.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_app.h"

typedef struct g_app_data_t
{
	ALLEGRO_DISPLAY* m_display;
	ALLEGRO_TIMER* m_logic_timer;
	ALLEGRO_EVENT_QUEUE* m_event_queue;
	bool m_is_running;
	bool m_update_logic;
} g_app_data_t;

static g_app_data_t g_data;

static void g_app_zero_initialize_data()
{
	g_data.m_display = NULL;
	g_data.m_logic_timer = NULL;
	g_data.m_event_queue = NULL;
	g_data.m_is_running = true;
	g_data.m_update_logic = false;
}

int32_t g_app_initialize()
{
	g_app_zero_initialize_data();

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

	s_log_print("Installing the keyboard - ");
	if (!al_install_keyboard())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_print("Installing the mouse - ");
	if (!al_install_mouse())
	{
		s_log_println("failure");
		return -1;
	}
	s_log_println("success");

	s_log_printf("Creating the display (%.1lf, %.1lf) - ", G_DISPLAY_INITIAL_SIZE.m_x, G_DISPLAY_INITIAL_SIZE.m_y);

	al_set_new_window_title(G_TITLE);
	al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
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
	al_register_event_source(g_data.m_event_queue, al_get_keyboard_event_source());
	al_register_event_source(g_data.m_event_queue, al_get_mouse_event_source());

	s_log_println("Initialization end\n");
	s_log_flush();

	return 0;
}

void g_app_shutdown()
{
	s_log_println("Shutdown begin");

	if (g_data.m_event_queue)
	{
		al_destroy_event_queue(g_data.m_event_queue);
		s_log_println("The event queue has been destroyed");
		g_data.m_event_queue = NULL;
	}

	if (g_data.m_logic_timer)
	{
		al_destroy_timer(g_data.m_logic_timer);
		s_log_println("The timer has been destroyed");
		g_data.m_logic_timer = NULL;
	}

	if (g_data.m_display)
	{
		al_destroy_display(g_data.m_display);
		s_log_println("The display has been destroyed");
		g_data.m_display = NULL;
	}

	if (al_is_mouse_installed())
	{
		al_uninstall_mouse();
		s_log_println("The mouse has been uninstalled");
	}

	if (al_is_keyboard_installed())
	{
		al_uninstall_keyboard();
		s_log_println("The keyboard has been uninstalled");
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

		case ALLEGRO_EVENT_KEY_DOWN:
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				g_data.m_is_running = false;
			}
		} break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
		{
			g_data.m_is_running = false;
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
	// empty
}

/// <summary>Display is updated. The double buffer is set as the target bitmap. After it is drawn to, the display
/// gets set as the target bitmap. Then the double buffer is drawn to display.</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
static void g_app_draw()
{
	al_clear_to_color(S_COLOR_EIGENGRAU.m_al_color);

	al_flip_display();
}

void g_app_loop()
{
	al_start_timer(g_data.m_logic_timer);

	while (g_data.m_is_running)
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
