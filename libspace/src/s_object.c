#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_object.h"
#include "libspace/s_math.h"

s_model_t* m_model;
s_point_t m_point;
s_point_t m_velocity;
s_point_t m_acceleration;
float m_max_speed;
float m_facing;

void s_object_set_zero(s_object_t* object)
{
	if (!object)
	{
		return;
	}

	s_model_set_zero(&object->m_model);
	s_point_set_zero(&object->m_velocity);
	s_point_set_zero(&object->m_acceleration);
	object->m_rotate_velocity = 0.0f;
	object->m_rotate_acceleration = 0.0f;
	object->m_max_speed = 0.0f;
	object->m_facing = 0.0f;
}

void s_object_reset(s_object_t* object)
{
	if (!object)
	{
		return;
	}

	s_model_center_to_origin(&object->m_model);
	s_model_rotate(&object->m_model, -object->m_facing);
	object->m_facing = 0.0f;
}

void s_object_center(s_object_t* object)
{
	if (!object)
	{
		return;
	}

	s_model_center_to_origin(&object->m_model);
}

void s_object_center_to_point(s_object_t* object, const s_point_t* center)
{
	if (!object)
	{
		return;
	}

	if (!center)
	{
		return;
	}

	s_model_center_to_point(&object->m_model, center);
}

void s_object_center_to_point_f(s_object_t* object, float x, float y)
{
	if (!object)
	{
		return;
	}

	s_model_center_to_point_f(&object->m_model, x, y);
}

void s_object_translate(s_object_t* object, const s_point_t* delta)
{
	if (!object)
	{
		return;
	}

	if (!delta)
	{
		return;
	}

	s_model_translate_f(&object->m_model, delta->m_x, delta->m_y);
}

void s_object_translate_f(s_object_t* object, float x, float y)
{
	if (!object)
	{
		return;
	}

	s_model_translate_f(&object->m_model, x, y);
}

void s_object_rotate(s_object_t* object, float delta)
{
	if (!object)
	{
		return;
	}

	object->m_facing += delta;

	while (object->m_facing > S_PI_DOUBLE)
	{
		object->m_facing -= S_PI_DOUBLE;
	}

	while (object->m_facing < 0.0f)
	{
		object->m_facing += S_PI_DOUBLE;
	}

	s_model_rotate(&object->m_model, delta);
}

void s_object_update(s_object_t* object)
{
	float speed = 0.0f;

	if (!object)
	{
		return;
	}

	s_point_add(&object->m_velocity, &object->m_acceleration);

	s_point_set_zero(&object->m_acceleration);

	if (!s_math_is_zero_f(object->m_rotate_acceleration))
	{
		object->m_rotate_velocity += object->m_rotate_acceleration;
		object->m_rotate_acceleration = 0.0f;
	}

	speed = s_point_get_length(&object->m_velocity);

	if (speed >= object->m_max_speed)
	{
		speed = (object->m_max_speed / speed);
		s_point_multiply_f(&object->m_velocity, speed);
	}

	s_object_translate(object, &object->m_velocity);

	if (!s_math_is_zero_f(object->m_rotate_velocity))
	{
		s_object_rotate(object, object->m_rotate_velocity);
	}
}

void s_object_update_step(s_object_t* object)
{
	static float speed = 0.0f;
	static s_point_t step = { 0.0f, 0.0f };

	if (!object)
	{
		return;
	}

	s_point_add(&object->m_velocity, &object->m_acceleration);

	s_point_set_zero(&object->m_acceleration);

	if (!s_math_is_zero_f(object->m_rotate_acceleration))
	{
		object->m_rotate_velocity += object->m_rotate_acceleration;
		object->m_rotate_acceleration = 0.0f;
	}

	speed = s_point_get_length(&object->m_velocity);

	if (speed >= object->m_max_speed)
	{
		speed = (object->m_max_speed / speed);
		s_point_multiply_f(&object->m_velocity, speed);
	}

	s_point_set(&step, &object->m_velocity);
	s_point_multiply_f(&step, S_OBJECT_LOGIC_STEP_COUNT_SCALE);

	s_object_translate(object, &step);

	if (!s_math_is_zero_f(object->m_rotate_velocity))
	{
		s_object_rotate(object, object->m_rotate_velocity * S_OBJECT_LOGIC_STEP_COUNT_SCALE);
	}
}

void s_object_thrust(s_object_t* object, float thrust)
{
	if (!object)
	{
		return;
	}

	s_point_add_f(&object->m_acceleration, thrust * cosf(object->m_facing), thrust * sinf(object->m_facing));
}

void s_object_draw(const s_object_t* object, int32_t flag)
{
	if (!object)
	{
		return;
	}

	s_model_draw(&object->m_model, flag);
}
