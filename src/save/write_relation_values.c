#include "save_game_serialization.h"

void save_stream_write_relation_values(struct DisplayMenuRelationValues *state)
{
    unsigned int i;

    for (i = 0; i < 24; ++i)
        frame_write_save_value(&state->records[i].value, 1);
    for (i = 0; i < 24; ++i)
        save_stream_write_nibbles(&state->records[i].flags, 1);
    for (i = 0; i < 24; ++i)
        save_stream_write_nibbles(&state->records[i].unknown_02[0], 1);
}
asm(".align 2, 0");
