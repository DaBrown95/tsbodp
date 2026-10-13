#include "display_time.h"
#include "heap.h"

void display_time_clear(struct DisplayTimeRecord *time)
{
    heap_clear(time, 0, 8);
}
asm(".align 2, 0");
