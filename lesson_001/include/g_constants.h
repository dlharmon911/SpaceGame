#ifndef _HEADER_GUARD_CONSTANTS_H_
#define _HEADER_GUARD_CONSTANTS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>

/// <summary>Title of the game</summary>
static const char* const G_TITLE = "Lesson 001 - Laying down the ground work!";

/// <summary>Version number of the series</summary>
static const char* const G_VERSION = "0.0.1";

/// <summary>Constant for the initial display size</summary>
static const s_point_t G_DISPLAY_INITIAL_SIZE = { 800.0f, 600.0f };

/// <summary>Constant for the timer tick count per second</summary>
static const double G_LOGIC_TIMER_RATE = 60.0;

#endif // !_HEADER_GUARD_CONSTANTS_H_
