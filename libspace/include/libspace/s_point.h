#ifndef _HEADER_GUARD_LIBSPACE_POINT_H_
#define _HEADER_GUARD_LIBSPACE_POINT_H_

#include <stdint.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "libspace/s_base.h"

enum S_POINT_FLOAT_INFO
{
	/// <summary>Size of the float array for a point struct. </summary>
	S_POINT_FLOAT_SIZE = 2
};

/// <summary>2D point structure. </summary>
typedef struct s_point_t
{
	union {
		struct {
			/// <summary>2D horizontal x value. </summary>
			float m_x;
			/// <summary>2D vertical y value. </summary>
			float m_y;
		};
		/// <summary>Float array as a union with the point's x and y values. </summary>
		float m_float_array[S_POINT_FLOAT_SIZE];
	};
} s_point_t;

/// <summary>Zero initialize point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_set_zero(s_point_t* point);

/// <summary>Add point (float version) to a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>n/a - no return</returns>
void s_point_add_f(s_point_t* point, float x, float y);

/// <summary>Subtract point (float version) from a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>n/a - no return</returns>
void s_point_subtract_f(s_point_t* point, float x, float y);

/// <summary>Multiply a point struct by a scalar value. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='scale'> - float scalar</param>
/// <returns>n/a - no return</returns>
void s_point_multiply_f(s_point_t* point, float scale);

/// <summary>Divide a point struct by a scalar value. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='scale'> - float scalar</param>
/// <returns>n/a - no return</returns>
void s_point_divide_f(s_point_t* point, float scale);

/// <summary>Compare if a point is equal to another point (float version). </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>bool - true if equal, false it not</returns>
bool s_point_equals_f(const s_point_t* point, float x, float y);

/// <summary>Set x and y values to point. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>n/a - no return</returns>
void s_point_set_f(s_point_t* point, float x, float y);

/// <summary>Add point struct to a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_add(s_point_t* point, const s_point_t* point2);

/// <summary>Subtract point struct from a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_subtract(s_point_t* point, const s_point_t* point2);

/// <summary>Multiply point struct to a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_multiply(s_point_t* point, const s_point_t* point2);

/// <summary>Divide a point struct by a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_divide(s_point_t* point, const s_point_t* point2);

/// <summary>Compare if a point struct is equal to another point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>bool - true if equal, false it not</returns>
bool s_point_equals(const s_point_t* point, const s_point_t* point2);

/// <summary>Set a point struct to a point struct. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_set(s_point_t* point, const s_point_t* point2);

/// <summary>Rotate a point struct around the origin. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='angle'> - float radians</param>
/// <returns>n/a - no return</returns>
void s_point_rotate(s_point_t* point, float angle);

/// <summary>Rotate an array of points around the origin. </summary>
/// <param name='point'> - pointer to point array</param>
/// <param name='count'> - size_t number of points in array</param>
/// <param name='angle'> - float radians</param>
/// <returns>n/a - no return</returns>
void s_point_rotate_array(s_point_t* point, size_t count, float angle);

/// <summary>Calculate difference between two points (result = point - point2). </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <param name='result'> - pointer to point data to store result</param>
/// <returns>n/a - no return</returns>
void s_point_get_difference(s_point_t* result, const s_point_t* point, const s_point_t* point2);

/// <summary>Calculate the length (magnitude) of a point. </summary>
/// <param name='point'> - pointer to point data</param>
/// <returns>float - returns the length</returns>
float s_point_get_length(const s_point_t* point);

/// <summary>Calculate the distance between two points. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>float - returns the distance</returns>
float s_point_get_distance_between(const s_point_t* point, const s_point_t* point2);

/// <summary>Calculate the dot product of two points. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='point2'> - pointer to point data</param>
/// <returns>float - returns the dot product</returns>
float s_point_dot_product(const s_point_t* point, const s_point_t* point2);

/// <summary>Normalizes a point to length 1.0f. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='result'> - pointer to point data to store result</param>
/// <returns>n/a - no return</returns>
void s_point_normalize(s_point_t* result, const s_point_t* point);

/// <summary>Find closest point on a line (line_point1 to line_point2) from a point. </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='line_point1'> - pointer to point data</param>
/// <param name='line_point2'> - pointer to point data</param>
/// <param name='result'> - pointer to point data to store result</param>
/// <returns>n/a - no return</returns>
void s_point_find_point_on_line(s_point_t* result, const s_point_t* point, const s_point_t* line_point1, const s_point_t* line_point2);

/// <summary>Calculate the distance from a point to a line (line_point1 to line_point2). </summary>
/// <param name='point'> - pointer to point data</param>
/// <param name='line_point1'> - pointer to point data</param>
/// <param name='line_point2'> - pointer to point data</param>
/// <returns>float - returns the distance</returns>
float s_point_line_point_distance(const s_point_t* point, const s_point_t* line_point1, const s_point_t* line_point2);

/// <summary>Translate a transform with the values in a point struct. </summary>
/// <param name='transform'> - pointer to transform data</param>
/// <param name='point'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_translate(ALLEGRO_TRANSFORM* transform, const s_point_t* point);

/// <summary>Translate a transform with the values of x and y. </summary>
/// <param name='transform'> - pointer to transform data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>n/a - no return</returns>
void s_point_translate_f(ALLEGRO_TRANSFORM* transform, float x, float y);

/// <summary>Scale a transform with the values in a point struct. </summary>
/// <param name='transform'> - pointer to transform data</param>
/// <param name='point'> - pointer to point data</param>
/// <returns>n/a - no return</returns>
void s_point_scale(ALLEGRO_TRANSFORM* transform, const s_point_t* point);

/// <summary>Scale a transform with the values of x and y. </summary>
/// <param name='transform'> - pointer to transform data</param>
/// <param name='x'> - x value of point data</param>
/// <param name='y'> - y value of point data</param>
/// <returns>n/a - no return</returns>
void s_point_scale_f(ALLEGRO_TRANSFORM* transform, float x, float y);

#endif // !_HEADER_GUARD_LIBSPACE_POINT_H_
