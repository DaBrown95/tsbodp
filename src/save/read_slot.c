#include "save_stream.h"

void save_stream_read_slot(unsigned int slot)
{
    save_stream_read_blocks(slot * 255 + 2, 255, g_save_stream_state.buffer);
}
asm(".align 2, 0");
