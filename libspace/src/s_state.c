#include <stdint.h>
#include "libspace/s_base.h"
#include "libspace/s_state.h"

void s_state_set_zero(s_state_t* state)
{
	if (!state)
	{
		return;
	}

	state->m_set_zero = NULL;
	state->m_initialize = NULL;
	state->m_destroy = NULL;
	state->m_logic = NULL;
	state->m_draw = NULL;
	state->m_data = NULL;
}
