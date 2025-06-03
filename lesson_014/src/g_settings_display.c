#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_settings.h"

void g_settings_populate_default_display_settings(g_settings_display_t* display)
{
	display->m_size.m_x = G_DISPLAY_INITIAL_SIZE.m_x;
	display->m_size.m_y = G_DISPLAY_INITIAL_SIZE.m_y;
}

int32_t g_settings_populate_display_settings(const ALLEGRO_CONFIG* config, g_settings_display_t* display)
{
	if (!display)
	{
		return -1;
	}

	display->m_size.m_x = s_config_get_value_as_float(config, "display", "width", display->m_size.m_x);
	display->m_size.m_y = s_config_get_value_as_float(config, "display", "height", display->m_size.m_y);

	return 0;
}

void g_settings_update_display_settings(ALLEGRO_CONFIG* config, const g_settings_display_t* display)
{
	s_config_set_value_as_float(config, "display", "width", display->m_size.m_x);
	s_config_set_value_as_float(config, "display", "height", display->m_size.m_y);
}
