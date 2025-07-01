#ifndef _HEADER_GUARD_STATS_H_
#define _HEADER_GUARD_STATS_H_

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <stdint.h>
#include <libspace.h>
#include "g_constants.h"

typedef struct g_stats_t
{
	s_point_t m_display_size;
	s_point_t* m_ship_position;
	size_t m_star_count;
	double m_fps;
} g_stats_t;

/// <summary>Draw statistics to the display</summary>
/// <param name='font'> - font to use to draw text</param>
/// <param name='stats'> - stats data struct</param>
/// <param name='x'> - horizontal starting position to draw statistics</param>
/// <param name='y'> - vertical starting position to draw statistics</param>
/// <returns>n/a - no return value</returns>
void g_stats_draw(const ALLEGRO_FONT* font, const g_stats_t* stats, float x, float y);

/// <summary>Set members of stats to zero point values</summary>
/// <param name='stats'> - stats data struct</param>
/// <returns>n/a - no return value</returns>
void g_stats_set_zero(g_stats_t* stats);

#endif // !_HEADER_GUARD_STATS_H_
