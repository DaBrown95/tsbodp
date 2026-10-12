#include "display_catalog_text.h"
const char *display_scene_lookup_text(unsigned int id)
{
    if (!display_text_load_string(id, g_display_text_buffer, 1024))
        return g_display_text_buffer;
    return 0;
}
