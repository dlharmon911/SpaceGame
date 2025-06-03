#ifndef _HEADER_GUARD_APPLICATION_H_
#define _HEADER_GUARD_APPLICATION_H_

#include <allegro5/allegro5.h>
#include <stdint.h>

/// <summary>Initialize application</summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>int32_t - returns 0 on success or -1 on error</returns>
int32_t g_app_initialize();

/// <summary>Application is shut down. All data is freed in the process. </summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
void g_app_shutdown();

/// <summary>Application continues to loop until signaled to close. </summary>
/// <param name='n/a'> - no parameters</param>
/// <returns>n/a - no return</returns>
void g_app_loop();

#endif // !_HEADER_GUARD_APPLICATION_H_
