#include "frame_random.h"
#include "resource_builders.h"

void frame_initialize_random_buffer(void)
{
    g_frame_random_buffer_address = (unsigned int)resource_allocate(2500);
}
