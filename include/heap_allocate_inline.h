#ifndef HEAP_ALLOCATE_INLINE_H
#define HEAP_ALLOCATE_INLINE_H
#include "heap.h"

/* The ordinary and zeroed allocators share this first-fit block operation. */
static __inline void *heap_allocate_inner(unsigned int allocation_bytes)
{
    unsigned int arena;
    allocation_bytes = (allocation_bytes + 15) & ~15;
    for (arena = 0; arena < g_heap_arena_count; ++arena) {
        struct HeapBlock *block = g_heap_arenas[arena].free;
        unsigned int capacity;
        if (block) {
            do {
                capacity = heap_block_bytes(block, arena);
                if (capacity >= allocation_bytes) goto available;
                block = block->next_free;
            } while (block);
        }
        continue;
    available:
        {
            if (capacity > allocation_bytes) {
                struct HeapBlock *after = (void *)((unsigned char *)block + 16 + allocation_bytes);
                heap_link_physical(block, after);
                heap_link_free(block, after);
            }
            heap_unlink_free(block, arena);
            block->next_free = (struct HeapBlock *)arena;
            block->previous_free = (struct HeapBlock *)-1;
            return block + 1;
        }
    }
    return 0;
}
#endif
