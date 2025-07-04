#ifndef _HEADER_GUARD_LIBSPACE_STATE_H_
#define _HEADER_GUARD_LIBSPACE_STATE_H_

#include <allegro5/allegro5.h>
#include <stdint.h>

typedef struct s_state_t
{
	void (*m_set_zero)(void* data);
	int32_t (*m_initialize)(void* data);
	void (*m_destroy)(void* data);
	void (*m_logic)(void* data);
	void (*m_draw)(const void* data);
	void* m_data;
} s_state_t;

void s_state_set_zero(s_state_t* state);

#endif // !_HEADER_GUARD_LIBSPACE_STATE_H_
