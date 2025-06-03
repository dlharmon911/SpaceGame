#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_textures.h"
#include "g_models.h"
#include "g_star.h"
#include "g_star_array.h"

void g_star_array_zero_initialize_data(g_star_array_t* star_array)
{
	if (!star_array)
	{
		return;
	}

	for (size_t i = 0; i < G_STAR_COUNT; ++i)
	{
		g_star_zero_initialize_data(&star_array->m_star[i]);
	}
	star_array->m_count = G_STAR_COUNT;
}

void g_star_array_draw(const g_star_array_t* star_array, int32_t flag)
{
	if (!star_array)
	{
		return;
	}

	for (size_t i = 0; i < G_STAR_COUNT; ++i)
	{
		g_star_draw(&star_array->m_star[i], flag);
	}
}

void g_star_array_scatter(ALLEGRO_BITMAP* texture, g_star_array_t* star_array)
{
	if (!texture)
	{
		return;
	}

	if (!star_array)
	{
		return;
	}

	const uint32_t scale[5] =
	{
		G_STAR_LAYER_01,
		G_STAR_LAYER_02,
		G_STAR_LAYER_03,
		G_STAR_LAYER_04,
		G_STAR_LAYER_05
	};
	size_t i = 0;
	uint32_t lower = 0;
	uint32_t upper = 0;
	g_star_t* star = NULL;

	for (size_t j = 0; j < 5; ++j)
	{
		upper += scale[j];

		for (size_t k = 0; k < scale[j]; ++k, ++i)
		{
			float a = (float)s_random_generate_constraint(lower, upper - 1);

			star = star_array->m_star + i;
			star->m_z = s_math_min_f(0.5f, (a / (float)G_STAR_COUNT) * 0.5f);

			g_model_generate_star_model(&star->m_star_model, &star->m_object.m_model, texture, star->m_z);

			s_point_t point =
			{
				s_random_generate_f(G_GAMESCREEN_SIZE.m_x - 1.0f) - G_GAMESCREEN_SIZE_HALF.m_x,
				s_random_generate_f(G_GAMESCREEN_SIZE.m_y - 1.0f) - G_GAMESCREEN_SIZE_HALF.m_y
			};

			s_model_translate(&star->m_object.m_model, &point);
		}

		lower = upper;
	}
}

void g_star_array_update(g_star_array_t* star_array, const s_point_t* ship_velocity)
{
	if (!ship_velocity)
	{
		return;
	}

	if (s_point_equals_f(ship_velocity, 0.0f, 0.0f))
	{
		return;
	}

	const float speed = s_point_get_length(ship_velocity) * G_STAR_SPEED;
	float angle = atan2f(ship_velocity->m_x, ship_velocity->m_y) + S_PI_HALF;
	const s_point_t velocity = { speed * cosf(angle), speed * sinf(angle) };
	g_star_t* star = NULL;

	for (size_t i = 0; i < G_STAR_COUNT; ++i)
	{
		star = &star_array->m_star[i];

		s_point_set_f(&star->m_object.m_velocity, velocity.m_x * star->m_z, -velocity.m_y * star->m_z);
		g_star_update(star);
	}
}

void g_star_array_update_step(g_star_array_t* star_array, const s_point_t* ship_velocity)
{
	float speed = 0.0f;
	float angle = 0.0f;
	s_point_t velocity = { 0.0f, 0.0f };
	g_star_t* star = NULL;

	if (!ship_velocity)
	{
		return;
	}

	if (s_point_equals_f(ship_velocity, 0.0f, 0.0f))
	{
		return;
	}

	speed = s_point_get_length(ship_velocity) * G_STAR_SPEED;

	speed = s_math_min_f(speed, G_STAR_MAX_SPEED);

	angle = atan2f(ship_velocity->m_x, ship_velocity->m_y) + S_PI_HALF;
	s_point_set_f(&velocity, speed * cosf(angle), speed * sinf(angle));

	for (size_t i = 0; i < G_STAR_COUNT; ++i)
	{
		star = &star_array->m_star[i];

		s_point_set_f(&star->m_object.m_velocity, velocity.m_x * star->m_z, -velocity.m_y * star->m_z);
		g_star_update_step(star);
	}
}

void g_star_array_apply_window_constraint(g_star_array_t* star_array, const s_point_t* top_left, const s_point_t* bottom_right)
{
	g_star_t* star = NULL;

	if (!star_array)
	{
		return;
	}

	for (size_t i = 0; i < G_STAR_COUNT; ++i)
	{
		star = &star_array->m_star[i];

		g_star_apply_window_constraint(star, top_left, bottom_right);
	}
}