#ifndef _HEADER_GUARD_CONSTANTS_H_
#define _HEADER_GUARD_CONSTANTS_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <libspace.h>

/// <summary>Title of the game</summary>
static const char* const G_TITLE = "Lesson 007 - Object of My Desire!";

/// <summary>Version number of the series</summary>
static const char* const G_VERSION = "0.0.7";

/// <summary>Constant for the initial display size</summary>
static const s_point_t G_DISPLAY_INITIAL_SIZE = { 800.0f, 600.0f };

enum
{
	G_GAMESCREEN_WIDTH = 800,
	G_GAMESCREEN_HEIGHT = 800
};

/// <summary>Constant for the screen size</summary>
static const s_point_t G_GAMESCREEN_SIZE = { (float)G_GAMESCREEN_WIDTH, (float)G_GAMESCREEN_HEIGHT };

/// <summary>Constant for the half of the screen size</summary>
static const s_point_t G_GAMESCREEN_SIZE_HALF = { 0.5f * (float)G_GAMESCREEN_WIDTH, 0.5f * (float)G_GAMESCREEN_HEIGHT };

/// <summary>Constant for the screen size</summary>
static const s_point_t G_GAMESCREEN_SCALE = { 1.0f / (float)G_GAMESCREEN_WIDTH, 1.0f / (float)G_GAMESCREEN_HEIGHT };

/// <summary>Constant for the timer tick count per second</summary>
static const double G_LOGIC_TIMER_RATE = 60.0;

/// <summary>Max object speed</summary>
static const float G_OBJECT_MAX_SPEED = { 2.0f };

#endif // !_HEADER_GUARD_CONSTANTS_H_
