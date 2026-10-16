#include "startup_buffer.h"

void startup_allocate_buffer_03005e5c(void)
{
    g_startup_buffer_03005e5c = heap_allocate(8192);
}
