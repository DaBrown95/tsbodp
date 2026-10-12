#include "display_scene_lifecycle.h"
struct FrameObject *display_allocate_text_object(const char **text)
{
    struct FrameObject *base = frame_allocate_object(24);
    base->flags = 9;
    base->forced_visible = 1;
    base->double_tile_size = 0;
    base->display_layer = 0;
    base->display_palette = 0;
    base->display_tile = base->display_index;
    base->unknown_d1_6 = 1;
    display_text_update(base, text);
    return base;
}
