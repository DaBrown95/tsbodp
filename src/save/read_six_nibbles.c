#include "save_game_loading.h"

void save_stream_read_six_nibbles(struct SaveStreamSixNibbles *record)
{
    save_stream_read_nibbles(record->values, 5);
    save_stream_read_nibbles(&record->first, 1);
}
asm(".align 2, 0");
