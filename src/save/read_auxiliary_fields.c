#include "save_game_loading.h"

void save_stream_read_auxiliary_fields(void)
{
    unsigned char *last = (unsigned char *)&g_save_auxiliary_fields + 14;
    unsigned short first, second;
    unsigned char tail;

    frame_load_save_value(last, 1);
    frame_load_save_value(last - 1, 1);
    frame_load_save_value(last - 2, 1);
    frame_load_save_value(&first, 2);
    frame_load_save_value(&second, 2);
    ((union SaveStreamHalfwordField *)(last - 14))->word =
        (unsigned int)first << 16;
    ((union SaveStreamHalfwordField *)(last - 10))->word =
        (unsigned int)second << 16;
    frame_load_save_value(&tail, 1);
    ((union SaveStreamByteField *)(last - 6))->word =
        (unsigned int)tail << 24;
}
asm(".align 2, 0");
