#include "frame_map_scene.h"
#include "display_object_palette.h"

void frame_set_subtype_object_palette(struct FrameObject *object,
                                      const void *const *resources)
{
    frame_set_object_palette(object, resources + object->unknown_0a);
}
