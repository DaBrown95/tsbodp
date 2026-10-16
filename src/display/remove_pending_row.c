#include "display_pending_mutation.h"

void display_remove_pending_row(unsigned short line)
{
    int index = 0;
    unsigned int bytes;
    while (DISPLAY_PENDING_ROWS.pending) {
    }
    while (DISPLAY_PENDING_ROWS.queued[index].line != line)
        ++index;
    bytes = (11 - index) * sizeof(struct DisplayPendingRow);
    heap_move(&DISPLAY_PENDING_ROWS.queued[index],
        &DISPLAY_PENDING_ROWS.queued[index + 1], bytes);
    DISPLAY_PENDING_ROWS.pending = 1;
}
