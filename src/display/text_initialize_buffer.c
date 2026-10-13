#include "display_text_bank.h"
#include "heap.h"

void display_text_initialize_buffer(void)
{
    display_text_select_bank(0);
    g_display_text_buffer = heap_allocate(1024);
}
asm(".align 2, 0");
