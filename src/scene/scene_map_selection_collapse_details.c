#include "scene_map_selection.h"
#include "display_motion.h"
#include "display_palette_lifecycle.h"
#include "frame_scene_motion.h"

unsigned int scene_map_selection_collapse_details(void)
{
    if (g_display_background_system.backgrounds[3].position_y == 0x100000) {
        register unsigned char *base_address asm("r1") =
            (unsigned char *)&g_display_background_system;
        /* The wide offset preserves the native R2 lifetime with the pinned
         * compiler. Its low word is the scroll-duration field's byte offset. */
        register unsigned long long duration_offset asm("r2") =
            (unsigned int)((unsigned char *)&g_display_background_system.backgrounds[3].scroll_duration -
                           (unsigned char *)&g_display_background_system);
        register unsigned short *duration_address asm("r0") =
            (unsigned short *)(base_address + (unsigned int)duration_offset);
        if (!*duration_address)
            return 1;
    } else if (!g_display_background_system.backgrounds[3].scroll_duration) {
        display_set_background_scroll_target(3, 0, 0x100000, 4);
        g_display_scene_frame_objects[2]->flags &= ~1U;
        display_remove_palette_block(g_scene_map_selection_palette_block);
        if (g_display_scene_frame_objects[3])
            g_display_scene_frame_objects[3]->flags =
                (g_display_scene_frame_objects[3]->flags & ~1U) | 2;
    }
    return 0;
}
