#include <allegro5/allegro5.h>
#include <stdint.h>
#include <stdio.h>
#include "libspace/s_base.h"
#include "libspace/s_screenshot.h"
#include "libspace/s_string.h"

static const char* S_SCREENSHOT_FILENAME_PREFIX = { "screenshot" };
static const char* S_SCREENSHOT_FILENAME_SUFFIX = { "png" };
static const char* S_SCREENSHOT_FILENAME_FORMAT = { "%s_%02d.%s" };

enum
{
	S_SCREENSHOT_STRING_ARRAY_MAX_SIZE = 256
};

void s_screenshot_save(ALLEGRO_BITMAP* bitmap)
{
	int32_t index = -1;
	char filename[S_SCREENSHOT_STRING_ARRAY_MAX_SIZE] = { 0 };

	do
	{
		++index;
		sprintf_s(filename, S_SCREENSHOT_STRING_ARRAY_MAX_SIZE, S_SCREENSHOT_FILENAME_FORMAT, S_SCREENSHOT_FILENAME_PREFIX, index, S_SCREENSHOT_FILENAME_SUFFIX);
	} while (al_filename_exists(filename));

	al_save_bitmap(filename, bitmap);
}
