#include "heap_allocate_inline.h"

void *heap_allocate(unsigned int bytes)
{
    return heap_allocate_inner(bytes);
}
