#include "display_pending_mutation.h"

void display_insert_pending_row(unsigned short line, unsigned short auxiliary,
    void (*apply)(unsigned int *, unsigned int *))
{
    int index = 0;
    unsigned int bytes;
    while (DISPLAY_PENDING_ROWS.pending) {
    }
    while (DISPLAY_PENDING_ROWS.queued[index].line < line)
        ++index;
    bytes = (10 - index) * sizeof(struct DisplayPendingRow);
    heap_move(&DISPLAY_PENDING_ROWS.queued[index + 1],
        &DISPLAY_PENDING_ROWS.queued[index], bytes);
    DISPLAY_PENDING_ROWS.queued[index].line = line;
    DISPLAY_PENDING_ROWS.queued[index].unknown02 = auxiliary;
    DISPLAY_PENDING_ROWS.queued[index].apply = apply;
    DISPLAY_PENDING_ROWS.pending = 1;
}
