#ifndef _HEADER_GUARD_CONSTANTS_H_
#define _HEADER_GUARD_CONSTANTS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>

/// <summary>Title of the game</summary>
static const char* const G_TITLE = "Lesson 018 - States!";

/// <summary>Version number of the series</summary>
static const char* const G_VERSION = "0.0.18";

/// <summary>Constant for the initial display size</summary>
static const s_point_t G_DISPLAY_INITIAL_SIZE = { 800.0f, 800.0f };

/// <summary>Constant for the view size</summary>
static const s_point_t G_GAME_VIEW_SIZE = { 800.0f, 800.0f };

enum
{
	/// <summary>Constant for the screen width</summary>
	G_GAMESCREEN_WIDTH = 1200,

	/// <summary>Constant for the screen height</summary>
	G_GAMESCREEN_HEIGHT = 1200
};

static const s_point_t G_GAMESCREEN_SIZE = { (float)G_GAMESCREEN_WIDTH, (float)G_GAMESCREEN_HEIGHT };

/// <summary>Constant for the half of the screen size</summary>
static const s_point_t G_GAMESCREEN_SIZE_HALF = { 0.5f * (float)G_GAMESCREEN_WIDTH, 0.5f * (float)G_GAMESCREEN_HEIGHT };

/// <summary>Constant for the top/left position of the screen</summary>
static const s_point_t G_GAMESCREEN_TOP_LEFT = { -(float)G_GAMESCREEN_WIDTH * 0.5f, -(float)G_GAMESCREEN_HEIGHT * 0.5f };

/// <summary>Constant for the bottom/right position of the screen</summary>
static const s_point_t G_GAMESCREEN_BOTTOM_RIGHT = { (float)G_GAMESCREEN_WIDTH * 0.5f, (float)G_GAMESCREEN_HEIGHT * 0.5f };

/// <summary>Constant for the timer tick count per second</summary>
static const double G_LOGIC_TIMER_RATE = 60.0;

#endif // !_HEADER_GUARD_CONSTANTS_H_
