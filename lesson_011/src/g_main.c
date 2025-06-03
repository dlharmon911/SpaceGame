#include "g_app.h"

int32_t main(int32_t argc, char** argv)
{
	if (g_app_initialize(argc, argv) == 0)
	{
		g_app_loop();
	}

	g_app_shutdown();

	return 0;
}
