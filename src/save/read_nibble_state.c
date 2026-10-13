#include "save_game_loading.h"

void save_stream_read_nibble_state(void)
{
    save_stream_read_nibbles(g_save_nibble_bytes.values, 8);
    frame_load_save_value(&g_save_nibble_bytes.tail, 1);
}
asm(".align 2, 0");
