#include "display_pending_block.h"

void display_pending_vcount_callback(void)
{
    DISPLAY_PENDING_ROWS.staging[g_display_pending_block_flag].apply(
        &DISPLAY_PENDING_ROWS.staging[g_display_pending_block_flag].value,
        &DISPLAY_PENDING_ROWS.staging[g_display_pending_block_flag].delta);
    ++g_display_pending_block_flag;
    if (!DISPLAY_PENDING_ROWS.staging[g_display_pending_block_flag].apply)
        g_display_pending_block_flag = 0;
    (*(volatile unsigned short *)0x04000004) &= 0xff;
    (*(volatile unsigned short *)0x04000004) |=
        DISPLAY_PENDING_ROWS.staging[g_display_pending_block_flag].line << 8;
}
