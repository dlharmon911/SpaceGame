#ifndef _HEADER_GUARD_LIBSPACE_COLLISION_H_
#define _HEADER_GUARD_LIBSPACE_COLLISION_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_triangle.h"
#include "libspace/s_circle.h"

bool s_collision_point_circle(const s_point_t* point, const s_circle_t* circle);
bool s_collision_point_circle_p(const s_point_t* point, const s_point_t* center, float radius);
bool s_collision_point_triangle(const s_point_t* point, const s_triangle_t* triangle);
bool s_collision_point_triangle_p(const s_point_t* point, const s_point_t* tpoint1, const s_point_t* tpoint2, const s_point_t* tpoint3);
bool s_collision_triangle_triangle(const s_triangle_t* triangle, const s_triangle_t* triangle2);
bool s_collision_triangle_circle(const s_triangle_t* triangle, const s_circle_t* circle);

#endif // !_HEADER_GUARD_LIBSPACE_COLLISION_H_
