#include "save_game_loading.h"

void save_stream_read_relation_values(struct DisplayMenuRelationValues *state)
{
    unsigned int i;

    for (i = 0; i < 24; ++i)
        frame_load_save_value(&state->records[i].value, 1);
    state->high_count = 0;
    for (i = 0; i < 24; ++i) {
        save_stream_read_nibbles(&state->records[i].flags, 1);
        if (state->records[i].flags & 4)
            ++state->high_count;
    }
    for (i = 0; i < 24; ++i)
        save_stream_read_nibbles(&state->records[i].unknown_02[0], 1);
    display_menu_refresh_relation(state);
}
asm(".align 2, 0");
