#include "heap.h"
void heap_merge_next(struct HeapBlock *block,unsigned int arena)
{
    struct HeapBlock *next=block->next;
    if(next && next->previous_free!=(struct HeapBlock*)-1) {
        if(next->previous_free) next->previous_free->next_free=next->next_free;
        if(next->next_free) next->next_free->previous_free=next->previous_free;
        block->next=next->next;
        if(next->next) next->next->previous=block;
    }
}

__asm__(".align 2, 0");
