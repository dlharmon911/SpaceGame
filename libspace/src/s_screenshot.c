#include <allegro5/allegro5.h>
#include <stdint.h>
#include <stdio.h>
#include "libspace/s_base.h"
#include "libspace/s_screenshot.h"
#include "libspace/s_file.h"

static const char* S_SCREENSHOT_FILENAME_PREFIX = { "screenshot" };
static const char* S_SCREENSHOT_FILENAME_SUFFIX = { "png" };

enum
{
	S_SCREENSHOT_FILENAME_MAX_SIZE = 256
};

void s_screenshot_save(ALLEGRO_BITMAP* bitmap)
{
	int32_t index = -1;
	char filename[S_SCREENSHOT_FILENAME_MAX_SIZE] = "";

	do
	{
		++index;
		sprintf_s(filename, S_SCREENSHOT_FILENAME_MAX_SIZE, "%s_%02d.%s", S_SCREENSHOT_FILENAME_PREFIX, index, S_SCREENSHOT_FILENAME_SUFFIX);
	} while (al_filename_exists(filename));

	al_save_bitmap(filename, bitmap);
}
