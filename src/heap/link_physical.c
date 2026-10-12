#include "heap.h"
void heap_link_physical(struct HeapBlock *block,struct HeapBlock *after)
{
    struct HeapBlock *next;
    after->previous=block;
    next=block->next;
    after->next=next;
    block->next=after;
    if(next) next->previous=after;
}
