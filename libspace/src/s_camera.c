#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_math.h"
#include "libspace/s_point.h"
#include "libspace/s_camera.h"

void s_camera_zero_initialize_data(s_camera_t* camera)
{
	if (!camera)
	{
		return;
	}

	s_point_set_zero(&camera->m_center);
	camera->m_following = NULL;
	s_point_set_zero(&camera->m_velocity);
}

void s_camera_set(s_camera_t* camera, const s_camera_t* camera2)
{
	if (!camera)
	{
		return;
	}

	if (!camera2)
	{
		return;
	}

	s_point_set(&camera->m_center, &camera2->m_center);
	camera->m_following = camera2->m_following;
	s_point_set(&camera->m_velocity, &camera2->m_velocity);
}

void s_camera_set_p(s_camera_t* camera, const s_point_t* center, s_point_t* following, const s_point_t* velocity)
{
	if (!camera)
	{
		return;
	}

	if (!center)
	{
		return;
	}

	if (!following)
	{
		return;
	}

	if (!velocity)
	{
		return;
	}

	s_point_set(&camera->m_center, center);
	camera->m_following = following;
	s_point_set(&camera->m_velocity, velocity);
}

const s_point_t* s_camera_get_center(const s_camera_t* camera)
{
	if (!camera)
	{
		return NULL;
	}

	return &camera->m_center;
}

const s_point_t* s_camera_get_following(const s_camera_t* camera)
{
	if (!camera)
	{
		return NULL;
	}

	return camera->m_following;
}

const s_point_t* s_camera_get_velocity(const s_camera_t* camera)
{
	if (!camera)
	{
		return NULL;
	}

	return &camera->m_velocity;
}

void s_camera_set_center(s_camera_t* camera, const s_point_t* center)
{
	if (!camera)
	{
		return;
	}
	
	s_point_set(&camera->m_center, center);
}

void s_camera_set_following(s_camera_t* camera, s_point_t* following)
{
	if (!camera)
	{
		return;
	}

	camera->m_following = following;
}

void s_camera_set_velocity(s_camera_t* camera, const s_point_t* velocity)
{
	if (!camera)
	{
		return;
	}

	s_point_set(&camera->m_velocity, velocity);
}

void s_camera_update(s_camera_t* camera)
{
	s_point_t difference = { 0.0f, 0.0f };
	float speed = {0.0f};
	float angle = { 0.0f };

	if (!camera)
	{
		return;
	}

	if (!camera->m_following)
	{
		return;
	}

	s_point_get_difference(&difference, camera->m_following, &camera->m_center);

	speed = s_point_get_length(&difference);

	if (!s_math_is_zero_f(speed))
	{
		angle = atan2f(difference.m_y, difference.m_x);

		speed = s_math_min_f(speed, S_CAMERA_MAX_SPEED);

		s_point_set_f(&camera->m_velocity, speed * cosf(angle), speed * sinf(angle));
	}

	s_point_add(&camera->m_center, &camera->m_velocity);
	s_point_set_zero(&camera->m_velocity);
}

void s_camera_translate_transform(ALLEGRO_TRANSFORM* transform, const s_camera_t* camera)
{
	al_translate_transform(transform, -camera->m_center.m_x, -camera->m_center.m_y);
}

