#include "g_app.h"

int32_t main(int32_t argc, char** argv)
{
	g_app_data_t* data = NULL;

	data = al_malloc(sizeof(g_app_data_t));

	if (!data)
	{
		return -1;
	}

	g_app_set_zero(data);

	if (g_app_initialize(argv[0], data) == 0)
	{
		g_app_loop(data);
	}

	g_app_shutdown(data);

	al_free(data);

	return 0;
}
