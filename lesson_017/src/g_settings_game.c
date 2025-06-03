#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_settings.h"

void g_settings_populate_default_game_settings(g_settings_game_t* game)
{
	game->m_draw_flag = S_MODEL_DRAW_FLAG_TEXTURED;
}

int32_t g_settings_populate_game_settings(const ALLEGRO_CONFIG* config, g_settings_game_t* game)
{
	if (!game)
	{
		return -1;
	}

	game->m_draw_flag = s_config_get_value_as_int32(config, "game", "draw_flag", game->m_draw_flag);

	return 0;
}

void g_settings_update_game_settings(ALLEGRO_CONFIG* config, const g_settings_game_t* game)
{
	s_config_set_value_as_int32(config, "game", "draw_flag", game->m_draw_flag);
}
