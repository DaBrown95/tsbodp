#include "save_game_serialization.h"

void save_stream_write_nibble_state(void)
{
    save_stream_write_nibbles(g_save_nibble_bytes.values, 8);
    frame_write_save_value(&g_save_nibble_bytes.tail, 1);
}
asm(".align 2, 0");
