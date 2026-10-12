#include "heap.h"
void heap_merge_previous(struct HeapBlock *block,unsigned int arena) {
    struct HeapBlock *previous=block->previous;
    if(previous && previous->previous_free!=(struct HeapBlock*)-1) {
        struct HeapBlock *first=g_heap_arenas[arena].free;
        struct HeapBlock *next=block->next_free;
        if(first==block) g_heap_arenas[arena].free=next;
        next->previous_free=0;
        previous->next=block->next;
        if(block->next) block->next->previous=previous;
    }
}
