#include <allegro5/allegro5.h>
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

static void g_app_set_zero()
{
	g_data.m_display = NULL;
	g_data.m_logic_timer = NULL;
	g_data.m_event_queue = NULL;
	g_data.m_is_running = true;
	g_data.m_update_logic = false;
}

int32_t g_app_initialize()
{
	g_app_set_zero();

	if (!al_init())
	{
		return -1;
	}

	if (!al_install_keyboard())
	{
		return -1;
	}

	if (!al_install_mouse())
	{
		return -1;
	}

	al_set_new_window_title(G_TITLE);
	al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
	if (!(g_data.m_display = al_create_display((int32_t)G_DISPLAY_INITIAL_SIZE.m_x, (int32_t)G_DISPLAY_INITIAL_SIZE.m_y)))
	{
		return -1;
	}

	if (!(g_data.m_logic_timer = al_create_timer(1.0 / G_LOGIC_TIMER_RATE)))
	{
		return -1;
	}

	if (!(g_data.m_event_queue = al_create_event_queue()))
	{
		return -1;
	}

	al_register_event_source(g_data.m_event_queue, al_get_display_event_source(g_data.m_display));
	al_register_event_source(g_data.m_event_queue, al_get_timer_event_source(g_data.m_logic_timer));
	al_register_event_source(g_data.m_event_queue, al_get_keyboard_event_source());
	al_register_event_source(g_data.m_event_queue, al_get_mouse_event_source());

	return 0;
}

void g_app_shutdown()
{
	if (g_data.m_event_queue)
	{
		al_destroy_event_queue(g_data.m_event_queue);
		g_data.m_event_queue = NULL;
	}

	if (g_data.m_logic_timer)
	{
		al_destroy_timer(g_data.m_logic_timer);
		g_data.m_logic_timer = NULL;
	}

	if (g_data.m_display)
	{
		al_destroy_display(g_data.m_display);
		g_data.m_display = NULL;
	}

	if (al_is_mouse_installed())
	{
		al_uninstall_mouse();
	}

	if (al_is_keyboard_installed())
	{
		al_uninstall_keyboard();
	}

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
	static ALLEGRO_EVENT event;

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
