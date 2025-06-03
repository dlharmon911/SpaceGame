#include <allegro5/allegro5.h>
#include <stdint.h>
#include "libspace/s_vector.h"

static const size_t S_VECTOR_CAPACITY_INITIAL = 32;
static const size_t S_VECTOR_CAPACITY_INCREMENT = 16;

typedef struct s_vector_t
{
	size_t m_capacity;
	size_t m_size;
	size_t m_object_size;
	void* m_data;
} s_vector_t;

typedef struct s_const_vector_t
{
	size_t m_capacity;
	size_t m_size;
	size_t m_object_size;
	void* m_data;
} s_const_vector_t;

s_vector_t* s_vector_create(size_t object_size)
{
	return s_vector_create_with_initial_capacity(object_size, S_VECTOR_CAPACITY_INITIAL);
}

s_vector_t* s_vector_create_with_initial_capacity(size_t object_size, size_t capacity)
{
	s_vector_t* vector = (s_vector_t*)al_malloc(sizeof(s_vector_t));

	if (!vector)
	{
		return NULL;
	}

	vector->m_size = 0;
	vector->m_capacity = 0;
	vector->m_object_size = object_size;
	vector->m_data = al_malloc(capacity * vector->m_object_size);

	if (!vector->m_data)
	{
		al_free(vector);
		return NULL;
	}

	vector->m_capacity = capacity;

	return vector;
}

void s_vector_destroy(s_vector_t* vector)
{
	if (vector)
	{
		if (vector->m_data)
		{
			al_free(vector->m_data);
		}
		al_free(vector);
	}
}

s_vector_t* s_vector_duplicate(const s_vector_t* vector)
{
	s_vector_t* v = s_vector_create(vector->m_object_size);

	if (v)
	{
		v->m_size = vector->m_size;
		v->m_capacity = vector->m_capacity;
		v->m_object_size = vector->m_object_size;
		v->m_data = al_malloc(vector->m_capacity * vector->m_object_size);

		if (v->m_data)
		{
			memcpy(v->m_data, vector->m_data, vector->m_capacity * vector->m_object_size);
		}
		else
		{
			s_vector_destroy(v);
			v = NULL;
		}
	}

	return v;
}

void s_vector_clear(s_vector_t* vector)
{
	void* temp = al_realloc(vector->m_data, S_VECTOR_CAPACITY_INITIAL * vector->m_object_size);

	if (temp)
	{
		vector->m_data = temp;
		vector->m_capacity = S_VECTOR_CAPACITY_INITIAL;
	}

	vector->m_size = 0;
}

static bool s_vector_increase_capacity(s_vector_t* vector, size_t capacity)
{
	void* temp = al_realloc(vector->m_data, capacity * vector->m_object_size);

	if (!temp)
	{
		temp = al_malloc(capacity * vector->m_object_size);

		ALLEGRO_ASSERT(temp);

		memcpy(temp, vector->m_data, vector->m_capacity * vector->m_object_size);

		al_free(vector->m_data);

		return false;
	}

	vector->m_data = temp;
	vector->m_capacity = capacity;

	return true;
}

bool s_vector_push_back(s_vector_t* vector, const void* data)
{
	if (!vector)
	{
		return false;
	}

	if (!data)
	{
		return false;
	}

	// if at capacity
	if (vector->m_size == vector->m_capacity && !s_vector_increase_capacity(vector, vector->m_capacity + S_VECTOR_CAPACITY_INCREMENT))
	{
		return false;
	}

	++vector->m_size;
	s_vector_set_value(vector, vector->m_size - 1, data);

	return true;
}

void s_vector_pop_back(s_vector_t* vector)
{
	if (!vector)
	{
		return;
	}

	if (vector->m_size == 0)
	{
		return;
	}

	--vector->m_size;

	if (vector->m_capacity > (vector->m_size + S_VECTOR_CAPACITY_INCREMENT))
	{
		size_t new_capacity = vector->m_capacity - S_VECTOR_CAPACITY_INCREMENT;

		void* temp = al_realloc(vector->m_data, new_capacity * vector->m_object_size);

		ALLEGRO_ASSERT(temp);

		vector->m_data = temp;
		vector->m_capacity = new_capacity;
	}
}

void s_vector_append_vector(s_vector_t* vector, const s_vector_t* vector2)
{
	s_vector_insert_vector(vector, vector2, vector->m_size);
}

void s_vector_insert_vector(s_vector_t* vector, const s_vector_t* vector2, size_t index)
{
	if (!vector)
	{
		return;
	}

	if (!vector2)
	{
		return;
	}

	if (vector->m_object_size != vector2->m_object_size)
	{
		return;
	}

	if (index > vector->m_size)
	{
		return;
	}

	// final size
	size_t fins_size = (vector->m_size + vector2->m_size);

	if (vector->m_capacity < fins_size)
	{
		size_t capacity = vector->m_capacity;
		while (capacity < fins_size)
		{
			capacity = capacity + S_VECTOR_CAPACITY_INCREMENT;
		}
		s_vector_increase_capacity(vector, capacity);
	}

	//if not at end, must shift data
	if (index < vector->m_size)
	{
		for (size_t i = 0; i < (vector->m_size - index); ++i)
		{
			char* dest = (char*)vector->m_data + ((fins_size - (i + 1)) * vector->m_object_size);
			const char* src = (char*)vector->m_data + ((vector->m_size - (i + 1)) * vector->m_object_size);

			memcpy((void*)dest, (const void*)src, vector->m_object_size);
		}
	}

	memcpy((char*)vector->m_data + (index * vector->m_object_size), (char*)vector2->m_data, vector2->m_size * vector2->m_object_size);
	vector->m_size = fins_size;
}

void s_vector_insert_value(s_vector_t* vector, const void* data, size_t index)
{
	// validate vector and data

	if (!vector)
	{
		return;
	}

	if (!data)
	{
		return;
	}

	if (index > vector->m_size)
	{
		return;
	}

	// get current size
	size_t size = vector->m_size;

	if (size == 0 || index == size)
	{
		s_vector_push_back(vector, data);
	}
	else
	{
		// temporarily add to back increasing capacity if needed
		s_vector_push_back(vector, data);

		for (size_t i = size; i > index; --i)
		{
			char* dest = (char*)vector->m_data + (i * vector->m_object_size);
			const char* src = (char*)vector->m_data + ((i - 1) * vector->m_object_size);

			memcpy((void*)dest, (const void*)src, vector->m_object_size);
		}
		memcpy((char*)vector->m_data + (index * vector->m_object_size), data, vector->m_object_size);
	}
}

void s_vector_remove_value(s_vector_t* vector, size_t index)
{
	if (!vector)
	{
		return;
	}

	if (index >= vector->m_size)
	{
		return;
	}

	if (index < (vector->m_size - 1))
	{
		memcpy((char*)vector->m_data + (index * vector->m_object_size),
			(const char*)vector->m_data + ((index + 1) * vector->m_object_size),
			(vector->m_size - (index + 1)) * vector->m_object_size);
	}

	s_vector_pop_back(vector);
}

void s_vector_set_value(s_vector_t* vector, size_t index, const void* data)
{
	ALLEGRO_ASSERT(vector && vector->m_data && index < vector->m_size);

	memcpy((void*)(((char*)vector->m_data) + (index * vector->m_object_size)), data, vector->m_object_size);
}

const void* s_vector_get_const_value(const s_vector_t* vector, size_t index)
{
	ALLEGRO_ASSERT(vector && vector->m_data && index < vector->m_size);

	return (void*)(((char*)vector->m_data) + (index * vector->m_object_size));
}

const void* s_vector_get_const_value_front(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector && vector->m_data && vector->m_size);

	return vector->m_data;
}

void* s_vector_get_value_front(s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector && vector->m_data && vector->m_size);

	return vector->m_data;
}

const void* s_vector_get_const_value_back(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector && vector->m_data && vector->m_size);

	return (void*)(((char*)vector->m_data) + ((vector->m_size - 1) * vector->m_object_size));
}

void* s_vector_get_value_back(s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector && vector->m_data && vector->m_size);

	return (void*)(((char*)vector->m_data) + ((vector->m_size - 1) * vector->m_object_size));
}

void* s_vector_get_value(s_vector_t* vector, size_t index)
{
	ALLEGRO_ASSERT(vector && vector->m_data && index < vector->m_size);

	return (void*)(((char*)vector->m_data) + (index * vector->m_object_size));
}

void* s_vector_get_data(s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector);
	return vector->m_data;
}

const void* s_vector_get_const_data(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector);
	return vector->m_data;
}

size_t s_vector_get_size(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector);
	return vector->m_size;
}

size_t s_vector_get_capacity(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector);
	return vector->m_capacity;
}

size_t s_vector_get_object_size(const s_vector_t* vector)
{
	ALLEGRO_ASSERT(vector);
	return vector->m_object_size;
}

bool s_vector_are_equal(const s_vector_t* vector1, const s_vector_t* vector2, int32_t(*func_compare)(const void* a, const void* b))
{
	if (vector1->m_size != vector2->m_size)
	{
		return false;
	}

	for (size_t i = 0; i < vector1->m_size; ++i)
	{
		const void* a = s_vector_get_const_value(vector1, i);
		const void* b = s_vector_get_const_value(vector2, i);

		if (func_compare(a, b))
		{
			return false;
		}
	}

	return true;
}

/***************************************************************************/

s_const_vector_t* s_const_vector_create_with_initial_capacity(size_t object_size, size_t capacity)
{
	return (s_const_vector_t*)s_vector_create_with_initial_capacity(object_size, capacity);
}

s_const_vector_t* s_const_vector_create(size_t object_size)
{
	return (s_const_vector_t*)s_vector_create(object_size);
}

void s_const_vector_destroy(s_const_vector_t* vector)
{
	s_vector_destroy((s_vector_t*)vector);
}

s_const_vector_t* s_const_vector_duplicate(const s_const_vector_t* vector)
{
	return (s_const_vector_t*)s_vector_duplicate((const s_vector_t*)vector);
}

void s_const_vector_clear(s_const_vector_t* vector)
{
	s_vector_clear((s_vector_t*)vector);
}

bool s_const_vector_push_back(s_const_vector_t* vector, const void* data)
{
	return s_vector_push_back((s_vector_t*)vector, data);
}

void s_const_vector_pop_back(s_const_vector_t* vector)
{
	s_vector_pop_back((s_vector_t*)vector);
}

void s_const_vector_append_vector(s_const_vector_t* vector, const s_const_vector_t* vector2)
{
	s_vector_append_vector((s_vector_t*)vector, (const s_vector_t*)vector2);
}

void s_const_vector_insert_vector(s_const_vector_t* vector, const s_const_vector_t* vector2, size_t index)
{
	s_vector_insert_vector((s_vector_t*)vector, (const s_vector_t*)vector2, index);
}

void s_const_vector_insert_value(s_const_vector_t* vector, const void* data, size_t index)
{
	s_vector_insert_value((s_vector_t*)vector, data, index);
}

void s_const_vector_remove_value(s_const_vector_t* vector, size_t index)
{
	s_vector_remove_value((s_vector_t*)vector, index);
}

void s_const_vector_set_value(s_const_vector_t* vector, size_t index, const void* data)
{
	s_vector_set_value((s_vector_t*)vector, index, data);
}

const void* s_const_vector_get_const_value(const s_const_vector_t* vector, size_t index)
{
	return s_vector_get_const_value((const s_vector_t*)vector, index);
}

const void* s_const_vector_get_const_data(const s_const_vector_t* vector)
{
	return s_vector_get_const_data((const s_vector_t*)vector);
}

size_t s_const_vector_get_size(const s_const_vector_t* vector)
{
	return s_vector_get_size((const s_vector_t*)vector);
}

size_t s_const_vector_get_capacity(const s_const_vector_t* vector)
{
	return s_vector_get_capacity((const s_vector_t*)vector);
}

size_t s_const_vector_get_object_size(const s_const_vector_t* vector)
{
	return s_vector_get_object_size((const s_vector_t*)vector);
}

bool s_const_vector_are_equal(const s_const_vector_t* vector1, const s_const_vector_t* vector2, int32_t(*func_compare)(const void* a, const void* b))
{
	return s_vector_are_equal((const s_vector_t*)vector1, (const s_vector_t*)vector2, func_compare);
}
