#include "save_stream.h"

void save_stream_end_transfer(void)
{
    g_save_display_status = g_save_saved_display_status;
}
asm(".align 2, 0");
