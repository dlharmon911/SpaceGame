#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_state_data.h"

void g_state_data_set_zero(g_state_data_t* data)
{
	if (!data)
	{
		return;
	}

	for (int32_t i = 0; i < G_STATE_COUNT; ++i)
	{
		s_state_set_zero(&data->m_state[i]);
	}

	data->m_index = G_STATE_INVALID;
}
