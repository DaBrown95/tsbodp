#include "heap.h"
void heap_unlink_free(struct HeapBlock *block,unsigned int arena)
{
    struct HeapBlock *previous=block->previous_free;
    if(previous) previous->next_free=block->next_free;
    else g_heap_arenas[arena].free=block->next_free;
    if(block->next_free) block->next_free->previous_free=block->previous_free;
}
