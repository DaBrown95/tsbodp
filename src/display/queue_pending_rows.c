#include "display_pending_block.h"

void display_queue_pending_rows(const void *source, unsigned int count)
{
    DISPLAY_PENDING_ROWS.count = count;
    while (DISPLAY_PENDING_ROWS.pending) {
    }
    display_reset_queued_rows();
    heap_copy(DISPLAY_PENDING_ROWS.queued, source, count * sizeof(struct DisplayPendingRow));
    DISPLAY_PENDING_ROWS.pending = 1;
}
