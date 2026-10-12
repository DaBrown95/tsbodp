#include "heap.h"
void *heap_allocate(unsigned int bytes)
{
    unsigned int arena;
    bytes=(bytes+15)&~15;
    for(arena=0;arena<g_heap_arena_count;++arena) {
        struct HeapBlock *block=g_heap_arenas[arena].free;
        unsigned int capacity;
        if(block) {
            do {
                capacity=heap_block_bytes(block,arena);
                if(capacity>=bytes) goto available;
                block=block->next_free;
            } while(block);
        }
        continue;
    available:
        {
            if(capacity>bytes) {
                struct HeapBlock *after=(void*)((unsigned char*)block+16+bytes);
                heap_link_physical(block,after);
                heap_link_free(block,after);
            }
            heap_unlink_free(block,arena);
            block->next_free=(struct HeapBlock*)arena;
            block->previous_free=(struct HeapBlock*)-1;
            return block+1;
        }
    }
    return 0;
}
