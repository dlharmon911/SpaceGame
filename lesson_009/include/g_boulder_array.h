#ifndef _HEADER_GUARD_BOULDER_ARRAY_H_
#define _HEADER_GUARD_BOULDER_ARRAY_H_

#include <allegro5/allegro5.h>
#include <stdint.h>
#include <string.h>
#include <libspace.h>
#include "g_constants.h"
#include "g_boulder.h"

enum
{
	G_BOULDER_INITIAL_COUNT = 20
};

typedef struct g_boulder_node_t
{
	g_boulder_t m_boulder;
	int32_t m_status;
} g_boulder_node_t;

typedef struct g_boulder_array_t
{
	s_vector_t* m_boulder_list;
} g_boulder_array_t;

void g_boulder_array_zero_initialize_data(g_boulder_array_t* boulder_array);
int32_t g_boulder_array_initialize(g_boulder_array_t* boulder_array, size_t initial_size);
void g_boulder_array_free(g_boulder_array_t* boulder_array);
void g_boulder_array_draw(const g_boulder_array_t* boulder_array, int32_t flag);
void g_boulder_array_scatter(ALLEGRO_BITMAP* texture, g_boulder_array_t* boulder_array);
void g_boulder_array_update(g_boulder_array_t* boulder_array);

#endif // !_HEADER_GUARD_BOULDER_ARRAY_H_
