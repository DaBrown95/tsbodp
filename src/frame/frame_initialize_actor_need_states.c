#include "frame_actor_initialization.h"
#include "frame_actor_needs.h"
#include "heap.h"

void frame_initialize_actor_need_states(void)
{
    g_frame_actor_need_states = heap_allocate(10 * sizeof(*g_frame_actor_need_states));
}
