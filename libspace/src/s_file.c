#include <allegro5/allegro5.h>
#include <stdint.h>
#include <stdio.h>
#include "libspace/s_base.h"
#include "libspace/s_file.h"

bool s_file_exists(const char* filename)
{
	ALLEGRO_FILE* file = al_fopen(filename, "rb");

	if (file)
	{
		al_fclose(file);
		return true;
	}
	return false;
}
