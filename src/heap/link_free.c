#include "heap.h"
void heap_link_free(struct HeapBlock *block,struct HeapBlock *after)
{
    struct HeapBlock *next;
    after->previous_free=block;
    next=block->next_free;
    after->next_free=next;
    block->next_free=after;
    if(next) next->previous_free=after;
}
