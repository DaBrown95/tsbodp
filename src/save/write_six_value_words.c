#include "save_game_serialization.h"

void save_stream_write_six_value_words(const int *values)
{
    unsigned int index;
    int value;

    for (index = 0; index < 6; ++index) {
        value = values[index] >> 16;
        frame_write_save_value(&value, 2);
    }
}
asm(".align 2, 0");
