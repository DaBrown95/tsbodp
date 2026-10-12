#include "heap.h"
void heap_free(void *memory)
{
    struct HeapBlock *block=(void*)((unsigned char*)memory-16);
    unsigned int arena=(unsigned int)block->next_free;
    heap_prepend_free(block,arena);
    heap_merge_next(block,arena);
    heap_merge_previous(block,arena);
}
__asm__(".align 2, 0");
