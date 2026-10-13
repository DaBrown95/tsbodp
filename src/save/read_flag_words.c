#include "save_game_loading.h"

void save_stream_read_flag_words(void)
{
    frame_load_save_value(&g_save_flag_words[0], 4);
    frame_load_save_value(&g_save_flag_words[1], 4);
    frame_load_save_value(&g_save_flag_words[2], 4);
    frame_load_save_value(&g_save_flag_words[3], 4);
}
asm(".align 2, 0");
