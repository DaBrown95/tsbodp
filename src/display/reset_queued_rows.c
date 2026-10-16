#include "display_pending_block.h"

void display_reset_queued_rows(void)
{
    int index;
    for (index = 0; index <= 11; ++index) {
        DISPLAY_PENDING_ROWS.queued[index].line |= 0xffff;
        DISPLAY_PENDING_ROWS.queued[index].unknown02 = 0;
        DISPLAY_PENDING_ROWS.queued[index].value = 0;
        DISPLAY_PENDING_ROWS.queued[index].delta = 0;
        DISPLAY_PENDING_ROWS.queued[index].apply = 0;
    }
}
