#include "heap.h"
void heap_initialize_arena(unsigned int arena,void *begin,void *end)
{
    struct HeapBlock *first=(void*)((unsigned char*)begin+16);
    struct HeapBlock *head;
    unsigned int bytes=(unsigned char*)end-(unsigned char*)begin-16;
    g_heap_arenas[arena].first=first;
    g_heap_arenas[arena].free=first;
    g_heap_arenas[arena].bytes=bytes;
    g_heap_arenas[arena].end=end;
    head=g_heap_arenas[arena].first;
    head->next=0;
    head->previous=0;
    head->next_free=0;
    head->previous_free=0;
    ++g_heap_arena_count;
}
