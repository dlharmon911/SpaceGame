#ifndef _HEADER_GUARD_LIBSPACE_LIBRARY_H_
#define _HEADER_GUARD_LIBSPACE_LIBRARY_H_

/*
 *       _       _ _
 *      | |     (_) |
 *      | |      _| | _   ___ ____   ____  ____ ____
 *      | |     | | || \ /___)  _ \ / _  |/ ___) _  )
 *      | |_____| | |_) )___ | | | ( ( | ( (__( (/ /
 *      |_______)_|____/(___/| ||_/ \_||_|\____)____)
 *                           |_|
 *
 *      Main header file for the Space Game Library.
 *      (separate modules can be included from the libspace/ directory)
 *
 *      By Daniel Harmon.
 *
 *      See readme.txt for copyright information.
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "libspace/s_base.h"
#include "libspace/s_flags.h"
#include "libspace/s_color.h"
#include "libspace/s_random.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"
#include "libspace/s_viewport.h"
#include "libspace/s_triangle.h"
#include "libspace/s_input.h"
#include "libspace/s_log.h"
#include "libspace/s_model.h"
#include "libspace/s_vector.h"
#include "libspace/s_vertex.h"
#include "libspace/s_object.h"
#include "libspace/s_string.h"
#include "libspace/s_config.h"
#include "libspace/s_screenshot.h"
#include "libspace/s_collision.h"
#include "libspace/s_camera.h"

#ifdef __cplusplus
}
#endif

#endif // !_HEADER_GUARD_LIBSPACE_LIBRARY_H_
