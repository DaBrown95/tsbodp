#include "save_game_serialization.h"

void save_stream_write_flag_words(void)
{
    frame_write_save_value(&g_save_flag_words[0], 4);
    frame_write_save_value(&g_save_flag_words[1], 4);
    frame_write_save_value(&g_save_flag_words[2], 4);
    frame_write_save_value(&g_save_flag_words[3], 4);
}
asm(".align 2, 0");
