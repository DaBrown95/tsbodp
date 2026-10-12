#include "display_scene_lifecycle.h"
void display_allocate_object_tiles(struct FrameObject *object,
                                   struct DisplayTileResource *resource)
{
    object->display_index = display_allocate_tile_bytes(resource, object->display_bytes,
                                                        object->double_tile_size);
}
/* Zero-filled alignment after the pool-free Thumb function. */
__asm__(".align 2, 0");
