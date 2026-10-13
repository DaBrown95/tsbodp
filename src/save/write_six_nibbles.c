#include "save_game_serialization.h"

void save_stream_write_six_nibbles(struct SaveStreamSixNibbles *record)
{
    save_stream_write_nibbles(record->values, 5);
    save_stream_write_nibbles(&record->first, 1);
}
asm(".align 2, 0");
