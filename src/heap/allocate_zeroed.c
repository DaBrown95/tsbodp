#include "heap_allocate_inline.h"

void *heap_allocate_zeroed(unsigned int bytes)
{
    void *result;
    bytes = (bytes + 15) & ~15;
    result = heap_allocate_inner(bytes);
    if (result) heap_clear(result, 0, bytes);
    return result;
}
