#include "heap.h"

void *heap_resize_in_place(void *memory, unsigned int bytes)
{
    register struct HeapBlock *block asm("r6") = (void *)((unsigned char *)memory - 16);
    unsigned int arena = (unsigned int)block->next_free;
    unsigned int capacity;
    bytes = (bytes + 15) & ~15;
    capacity = heap_block_bytes(block, arena);
    if (bytes < capacity) {
        struct HeapBlock *after = (void *)((unsigned char *)memory + bytes);
        heap_link_physical(block, after);
        heap_prepend_free(after, arena);
        heap_merge_next(after, arena);
    } else if (bytes > capacity) {
        register unsigned int combined asm("r2");
        unsigned int next_capacity;
        block = block->next;
        next_capacity = heap_block_bytes(block, arena);
        next_capacity += 16;
        combined = capacity + next_capacity;
        if (block->previous_free == (struct HeapBlock *)-1 || bytes > combined) return 0;
        if (bytes < combined) {
            struct HeapBlock *after = (void *)((unsigned char *)memory + bytes);
            heap_link_physical(block, after);
            heap_link_free(block, after);
        }
        heap_unlink_free(block, arena);
        heap_unlink_physical(block, arena);
    }
    return memory;
}
