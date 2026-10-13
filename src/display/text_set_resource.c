#include "display_text_resource.h"

int display_text_set_resource(const void *data)
{
    const unsigned int *header = data;
    g_display_text_resource = data;
    {
        unsigned int offset = *header++;
        g_display_text_nodes = (void *)header;
        g_display_text_offsets = (void *)((const unsigned char *)data + offset);
    }
    return 0;
}
