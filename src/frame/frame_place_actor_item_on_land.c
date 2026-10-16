#include "frame_actor_items.h"
#include "frame_map.h"
#include "frame_terrain_classifier.h"

/* Explicit compiler constraints for genuine values; no instruction assembly.
 * X survives the Y/terrain calls in a callee-saved register.  The fully assigned
 * two-word point occupies the immediate terrain call's argument registers only. */
void frame_place_actor_item_on_land(struct FrameObject *object)
{
    struct FramePoint bounds;
    register int x asm("r4");
    int y;

    frame_get_map_dimensions(&bounds);
    do {
        x = frame_random_range(32, bounds.x - 32);
        y = frame_random_range(24, bounds.y - 24);
    } while (({
        register struct FramePoint argument asm("r0");
        argument.y = y;
        argument.x = x;
        frame_map_terrain_at(argument);
    }) != 0);
    frame_set_position(object, (unsigned int)x * 65536u,
                       (unsigned int)y * 65536u);
}
/* Preserve the original two zero-filled alignment bytes after the C symbol. */
asm(".align 2,0");
