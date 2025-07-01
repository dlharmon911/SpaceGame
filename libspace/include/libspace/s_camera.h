#ifndef _HEADER_GUARD_LIBSPACE_CAMERA_H_
#define _HEADER_GUARD_LIBSPACE_CAMERA_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"

static const float S_CAMERA_MAX_SPEED = 4.5f;
static const float S_CAMERA_MAX_DISTANCE = 200.0f;

enum
{
	S_CAMERA_FLOAT_SIZE = 2 * S_POINT_FLOAT_SIZE
};

typedef struct s_camera_t
{
	union
	{
		struct
		{
			s_point_t m_center;
			s_point_t m_velocity;
		};
		float m_float_array[S_CAMERA_FLOAT_SIZE];
	};
	s_point_t* m_following;
} s_camera_t;

/// <summary>Zero initialize a camera struct. </summary>
/// <param name='camera'> - pointer to camera data</param>
/// <returns>n/a - no return</returns>
void s_camera_set_zero(s_camera_t* camera);
void s_camera_set(s_camera_t* camera, const s_camera_t* camera2);
void s_camera_set_p(s_camera_t* camera, const s_point_t* center, s_point_t* following, const s_point_t* velocity);
const s_point_t* s_camera_get_center(const s_camera_t* camera);
const s_point_t* s_camera_get_following(const s_camera_t* camera);
const s_point_t* s_camera_get_velocity(const s_camera_t* camera);
void s_camera_set_center(s_camera_t* camera, const s_point_t* center);
void s_camera_set_following(s_camera_t* camera, s_point_t* following);
void s_camera_set_velocity(s_camera_t* camera, const s_point_t* velocity);
void s_camera_update(s_camera_t* camera);
void s_camera_translate_transform(ALLEGRO_TRANSFORM* transform, const s_camera_t* camera);

#endif // !_HEADER_GUARD_LIBSPACE_CAMERA_H_
