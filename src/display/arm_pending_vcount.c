#include "display_pending_block.h"

void display_arm_pending_vcount(void)
{
    g_display_pending_block_flag = 0;
    irq_set_vcount(DISPLAY_PENDING_ROWS.staging[0].line);
}
