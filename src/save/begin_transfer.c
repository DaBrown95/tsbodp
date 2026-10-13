#include "save_stream.h"

void save_stream_begin_transfer(void)
{
    g_save_saved_display_status = g_save_display_status;
    g_save_interrupt_ack = 0x3fff;
    g_save_display_status = 0;
    save_transfer_configure_4c8f4(0x40);
}
asm(".align 2, 0");
