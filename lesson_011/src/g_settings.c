#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_settings.h"

void g_settings_populate_default_display_settings(g_settings_display_t* display);
int32_t g_settings_populate_display_settings(const ALLEGRO_CONFIG* config, g_settings_display_t* display);
void g_settings_update_display_settings(ALLEGRO_CONFIG* config, const g_settings_display_t* display);

void g_settings_populate_default_game_settings(g_settings_game_t* game);
int32_t g_settings_populate_game_settings(const ALLEGRO_CONFIG* config, g_settings_game_t* game);
void g_settings_update_game_settings(ALLEGRO_CONFIG* config, const g_settings_game_t* game);

int32_t g_settings_populate_settings(const ALLEGRO_CONFIG* config, g_settings_t* settings);

int32_t g_settings_load(const char* filename, g_settings_t* settings)
{
	ALLEGRO_CONFIG* config = NULL;

	if (!filename)
	{
		return -1;
	}

	if (!settings)
	{
		return -1;
	}

	g_settings_populate_default_display_settings(&settings->m_display);
	g_settings_populate_default_game_settings(&settings->m_game);

	config = al_load_config_file(filename);
	if (!config)
	{
		return 0;
	}

	if (g_settings_populate_display_settings(config, &settings->m_display) < 0)
	{
		return -1;
	}

	if (g_settings_populate_game_settings(config, &settings->m_game) < 0)
	{
		return -1;
	}

	return 0;
}

int32_t g_settings_save(const char* filename, const g_settings_t* settings)
{
	ALLEGRO_CONFIG* config = NULL;

	if (!filename)
	{
		return -1;
	}

	if (!settings)
	{
		return -1;
	}

	config = al_create_config();
	if (!config)
	{
		return 1;
	}

	g_settings_update_display_settings(config, &settings->m_display);
	g_settings_update_game_settings(config, &settings->m_game);

	if (!al_save_config_file(filename, config))
	{
		return -1;
	}

	return 0;
}

int32_t g_settings_populate_settings(const ALLEGRO_CONFIG* config, g_settings_t* settings)
{
	if (!settings)
	{
		return -1;
	}

	if (g_settings_populate_display_settings(config, &settings->m_display) < 0)
	{
		return -1;
	}

	if (g_settings_populate_game_settings(config, &settings->m_game) < 0)
	{
		return -1;
	}

	return 0;
}
