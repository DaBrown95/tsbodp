#include "save_world_initialization.h"

void save_world_initialize(void)
{
    struct SaveWorldInitState *state = &g_save_world_init_state;
    unsigned char *initial_marker = (unsigned char *)state + 0x73f;
    unsigned int zero = 0;
    int *pending;
    int empty;
    *initial_marker = 14;
    display_time_copy(&state->prefix.clock, &g_save_default_clock);
    save_world_initialize_record(state->prefix.unknown10);
    actor_entry_reset((struct ActorEntryContext *)state->prefix.unknowndc);
    save_world_initialize_conditions();
    save_world_reset_transition_row(g_display_world_clock_selection.row);
    *((unsigned char *)state + 0x734) = zero;
    display_fill_bytes((unsigned char *)state + 0x724, 0, 8);
    display_fill_bytes((unsigned char *)state + 0x72c, 0, 8);
    pending = &state->pending;
    empty = -2;
    state->prefix.byte746 = 255;
    state->pending_columns = zero;
    *((unsigned char *)state + 0x42c) = 50;
    *((unsigned char *)state + 0x42d) = 1;
    *((unsigned char *)state + 0x43c) = 50;
    state->prefix.byte740 = 42;
    state->prefix.byte741 = zero;
    state->prefix.byte742 = zero;
    *pending = empty;
}
asm(".align 2, 0");
