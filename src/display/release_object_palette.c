#include "frame_map_scene.h"
#include "display_object_palette.h"

void frame_release_object_palette(struct FrameObject *object)
{
    if (object->flags & 0x08000000) {
        unsigned int slot = object->display_palette;
        unsigned char *base = (unsigned char *)&g_frame_map_palette_state;
        /* This access view starts before the slot: id +4, users +6. */
        unsigned char *record = base + slot * 8;

        if (record[6]) {
            if (--record[6] == 0 && slot > 7 && slot <= 15)
                record[4] = 255;
        }
    }
}
asm(".align 2, 0");
