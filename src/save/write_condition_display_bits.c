#include "save_condition_state.h"

void save_stream_write_condition_display_bits(void)
{
    frame_write_save_value(g_condition_display_bits, 15);
}

asm(".align 2, 0");
