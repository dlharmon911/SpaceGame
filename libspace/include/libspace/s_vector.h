#ifndef _HEADER_GUARD_LIBSPACE_VECTOR_H_
#define _HEADER_GUARD_LIBSPACE_VECTOR_H_

#include <allegro5/allegro5.h>
#include <stdint.h>

typedef struct s_vector_t s_vector_t;
typedef struct s_const_vector_t s_const_vector_t;

s_vector_t* s_vector_create(size_t object_size);
s_vector_t* s_vector_create_with_initial_capacity(size_t object_size, size_t capacity);
void s_vector_destroy(s_vector_t* vector);
s_vector_t* s_vector_duplicate(const s_vector_t* vector);
void s_vector_clear(s_vector_t* vector);
bool s_vector_push_back(s_vector_t* vector, const void* data);
void s_vector_pop_back(s_vector_t* vector);
void s_vector_append_vector(s_vector_t* vector, const s_vector_t* vector2);
void s_vector_insert_vector(s_vector_t* vector, const s_vector_t* vector2, size_t index);
void s_vector_insert_value(s_vector_t* vector, const void* data, size_t index);
void s_vector_remove_value(s_vector_t* vector, size_t index);
void s_vector_set_value(s_vector_t* vector, size_t index, const void* data);
const void* s_vector_get_const_value(const s_vector_t* vector, size_t index);
const void* s_vector_get_const_value_front(const s_vector_t* vector);
void* s_vector_get_value_front(s_vector_t* vector);
const void* s_vector_get_const_value_back(const s_vector_t* vector);
void* s_vector_get_value_back(s_vector_t* vector);
void* s_vector_get_value(s_vector_t* vector, size_t index);
void* s_vector_get_data(s_vector_t* vector);
const void* s_vector_get_const_data(const s_vector_t* vector);
size_t s_vector_get_size(const s_vector_t* vector);
size_t s_vector_get_capacity(const s_vector_t* vector);
size_t s_vector_get_object_size(const s_vector_t* vector);
bool s_vector_are_equal(const s_vector_t* vector1, const s_vector_t* vector2, int32_t(*func_compare)(const void* a, const void* b));

/********************************************************************************/

s_const_vector_t* s_const_vector_create(size_t object_size);
s_const_vector_t* s_const_vector_create_with_initial_capacity(size_t object_size, size_t capacity);
void s_const_vector_destroy(s_const_vector_t* vector);
s_const_vector_t* s_const_vector_duplicate(const s_const_vector_t* vector);
void s_const_vector_clear(s_const_vector_t* vector);
bool s_const_vector_push_back(s_const_vector_t* vector, const void* data);
void s_const_vector_pop_back(s_const_vector_t* vector);
void s_const_vector_append_vector(s_const_vector_t* vector, const s_const_vector_t* vector2);
void s_const_vector_insert_vector(s_const_vector_t* vector, const s_const_vector_t* vector2, size_t index);
void s_const_vector_insert_value(s_const_vector_t* vector, const void* data, size_t index);
void s_const_vector_remove_value(s_const_vector_t* vector, size_t index);
void s_const_vector_set_value(s_const_vector_t* vector, size_t index, const void* data);
const void* s_const_vector_get_const_value(const s_const_vector_t* vector, size_t index);
const void* s_const_vector_get_const_data(const s_const_vector_t* vector);
size_t s_const_vector_get_size(const s_const_vector_t* vector);
size_t s_const_vector_get_capacity(const s_const_vector_t* vector);
size_t s_const_vector_get_object_size(const s_const_vector_t* vector);
bool s_const_vector_are_equal(const s_const_vector_t* vector1, const s_const_vector_t* vector2, int32_t(*func_compare)(const void* a, const void* b));

#endif // !_HEADER_GUARD_LIBSPACE_VECTOR_H_
