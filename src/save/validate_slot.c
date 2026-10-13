#include "save_stream.h"

unsigned int save_stream_validate_slot(unsigned int slot)
{
    unsigned int checksum = save_stream_checksum(g_save_stream_state.buffer, 2040);
    unsigned int valid = 0;
    if (checksum == 0) valid = 1;
    g_save_stream_state.valid[slot] = valid;
    return valid;
}
asm(".align 2, 0");
