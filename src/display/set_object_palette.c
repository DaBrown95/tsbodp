#include "frame_map_scene.h"
#include "display_object_palette.h"

void frame_set_object_palette(struct FrameObject *object, const void *input)
{
    const void *const *resources = input;
    unsigned int slot = frame_find_object_palette_slot(resources);

    object->display_palette = slot;
    g_frame_map_palette_state.slots[slot].id = object->id;
    g_frame_map_palette_state.slots[slot].unknown01 = object->unknown_0a;
    g_frame_map_palette_state.slots[slot].users++;
    g_frame_map_palette_state.slots[slot].sources = resources;
    resources += g_frame_map_palette_state.frame;
    display_load_palette_alternate(*resources, slot << 4, 16);
    object->flags |= 0x08000000;
}
asm(".align 2, 0");
