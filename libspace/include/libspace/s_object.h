#ifndef _HEADER_GUARD_LIBSPACE_OBJECT_H_
#define _HEADER_GUARD_LIBSPACE_OBJECT_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_point.h"
#include "libspace/s_model.h"

enum
{
	S_OBJECT_LOGIC_STEP_COUNT = 16
};

static const float S_OBJECT_LOGIC_STEP_COUNT_SCALE = 1.0f / (float)S_OBJECT_LOGIC_STEP_COUNT;

/// <summary>Data struct for object data</summary>
typedef struct s_object_t
{
	/// <summary>Model data container</summary>
	s_model_t m_model;

	/// <summary>Movement velocity of object</summary>
	s_point_t m_velocity;

	/// <summary>Movement acceleration of object</summary>
	s_point_t m_acceleration;

	/// <summary>Rotational velocity of object</summary>
	float m_rotate_velocity;

	/// <summary>Rotational acceleration of object</summary>
	float m_rotate_acceleration;

	/// <summary>Object specific maximum speed</summary>
	float m_max_speed;

	/// <summary>Angle object is facing</summary>
	float m_facing;
} s_object_t;

/// <summary>Zero-initializes data struct</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <returns>n/a</returns>
void s_object_zero_initialize_data(s_object_t* object);

/// <summary>Resets object position/rotation to zero</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <returns>n/a</returns>
void s_object_reset(s_object_t* object);

/// <summary>Translate model vertices to origin (0, 0, 0)</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <returns>n/a</returns>
void s_object_center(s_object_t* object);

/// <summary>Translate model vertices to center given</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='center'> - vertex of center to translate to</param>
/// <returns>n/a</returns>
void s_object_center_to_point(s_object_t* object, const s_point_t* center);

/// <summary>Translate model vertices to center given (float version)</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='x'> - x coordinates of center</param>
/// <param name='y'> - y coordinates of center</param>
/// <param name='z'> - z coordinates of center</param>
/// <returns>n/a</returns>
void s_object_center_to_point_f(s_object_t* object, float x, float y);

/// <summary>Translate model vertices</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='delta'> - point coordinates of translate amount</param>
/// <returns>n/a</returns>
void s_object_translate(s_object_t* object, const s_point_t* delta);

/// <summary>Translate model vertices (float version)</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='x'> - x coordinates of translate amount</param>
/// <param name='y'> - y coordinates of translate amount</param>
/// <param name='z'> - z coordinates of translate amount</param>
/// <returns>n/a</returns>
void s_object_translate_f(s_object_t* object, float x, float y);

/// <summary>Rotate model vertices</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='delta'> - angle of rotation amount</param>
/// <returns>n/a</returns>
void s_object_rotate(s_object_t* object, float delta);

/// <summary>Updates object movement/rotation</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <returns>n/a</returns>
void s_object_update(s_object_t* object);

/// <summary>Updates object movement/rotation</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <returns>n/a</returns>
void s_object_update_step(s_object_t* object);

/// <summary>Accelerate object</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='thrust'> - amount to add to object acceleration</param>
/// <returns>n/a</returns>
void s_object_thrust(s_object_t* object, float thrust);

/// <summary>Draws object to display</summary>
/// <param name='object'> - pointer to container of object data</param>
/// <param name='flag'> - draw flag (textured, outline, etc.)</param>
/// <returns>n/a</returns>
void s_object_draw(const s_object_t* object, int32_t flag);

#endif // !_HEADER_GUARD_LIBSPACE_OBJECT_H_
