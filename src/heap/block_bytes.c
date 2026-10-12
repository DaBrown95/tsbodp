#include "heap.h"
unsigned int heap_block_bytes(struct HeapBlock *block,unsigned int arena)
{
    unsigned char *next=(void*)block->next;
    if(!next) next=g_heap_arenas[arena].end;
    return next-(unsigned char*)block-16;
}
