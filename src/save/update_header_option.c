#include "save_stream.h"

unsigned int save_stream_update_header_option(void)
{
    g_save_stream_state.header.bytes[10] = save_current_header_option_44ffc();
    g_save_stream_state.header.bytes[11] = 1;
    return 1;
}
asm(".align 2, 0");
