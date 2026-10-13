#include "save_game_loading.h"

void save_stream_read_world_fields(void)
{
    unsigned char *last = (unsigned char *)&g_save_world_fields + 0x42e;
    unsigned short first, second;

    save_stream_read_bits(last, 1);
    save_stream_read_nibbles(last - 1, 1);
    frame_load_save_value(last - 2, 1);
    frame_load_save_value(&first, 2);
    frame_load_save_value(&second, 2);
    ((union SaveStreamHalfwordField *)(last - 10))->word =
        (unsigned int)first << 16;
    ((union SaveStreamHalfwordField *)(last - 6))->word =
        (unsigned int)second << 16;
}
asm(".align 2, 0");
