#include "heap.h"
void heap_unlink_physical(struct HeapBlock *block,unsigned int arena)
{
    struct HeapBlock *previous=block->previous;
    if(previous) previous->next=block->next;
    else g_heap_arenas[arena].first=block->next;
    if(block->next) block->next->previous=block->previous;
}
