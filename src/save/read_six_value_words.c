#include "save_game_loading.h"

void save_stream_read_six_value_words(int *values)
{
    unsigned int i = 0, value;
    int *cursor;

    cursor = values;
    do {
        frame_load_save_value(&value, 2);
        *cursor++ = value << 16;
    } while (++i < 6);
}
asm(".align 2, 0");
