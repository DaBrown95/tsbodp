#include "save_condition_state.h"

void save_stream_read_condition_display_bits(void)
{
    frame_load_save_value(g_condition_display_bits, 15);
}

asm(".align 2, 0");
