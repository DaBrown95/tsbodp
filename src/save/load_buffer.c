#include "save_game_loading.h"

void save_stream_load_buffer(void)
{
    g_save_stream_state.cursor = g_save_stream_state.buffer;
    g_save_stream_state.bit_offset = 0;
    save_stream_load_game_state();
    g_save_stream_state.used = g_save_stream_state.cursor - g_save_stream_state.buffer;
    g_save_stream_state.percentage = g_save_stream_state.used * 100 / 2040;
}
asm(".align 2, 0");
