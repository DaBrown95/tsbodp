#include "heap.h"
void heap_prepend_free(struct HeapBlock *block,unsigned int arena)
{
    struct HeapBlock *first;
    block->previous_free=0;
    first=g_heap_arenas[arena].free;
    block->next_free=first;
    g_heap_arenas[arena].free=block;
    if(first) first->previous_free=block;
}
