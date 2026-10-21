#include "frame_animation.h"

/* These existing provisional collider member names are physical byte slots:
 * x/y are signed left/right and width/height are signed top/bottom here.
 * Valid inputs require live compatible owners and collider_count <= 2. */
int frame_bounds_overlap_unrooted_1107c(struct FrameAnimationObject *first,
                                       struct FrameAnimationObject *other)
{
    struct FramePoint position = other->next_position;
    int top = (position.y >> 16) + (signed char)other->bound_y1;
    int bottom = (position.y >> 16) + (signed char)other->bound_y2;
    int left, right;
    unsigned int i;

    if (other->display.flips.mirrored_x < 0) {
        left = (position.x >> 16) - (signed char)other->bound_x2;
        right = (position.x >> 16) - (signed char)other->bound_x1;
    } else {
        left = (position.x >> 16) + (signed char)other->bound_x1;
        right = (position.x >> 16) + (signed char)other->bound_x2;
    }
    for (i = 0; i < first->collider_count; i++) {
        const struct FrameCollider *collider = &first->colliders[i];
        if (first->colliders[i].kind) {
            int first_top, first_bottom, first_left, first_right;
            int overlap;
            position = first->next_position;
            first_top = (position.y >> 16) + (signed char)first->colliders[i].width;
            first_bottom = (position.y >> 16) + (signed char)first->colliders[i].height;
            if (first->display.flips.mirrored_x < 0) {
                first_left = (position.x >> 16) - (signed char)collider->y;
                first_right = (position.x >> 16) - (signed char)collider->x;
            } else {
                first_left = (position.x >> 16) + (signed char)collider->x;
                first_right = (position.x >> 16) + (signed char)collider->y;
            }
            overlap = 1;
            if (right < first_left) overlap = 0;
            else if (left > first_right) overlap = 0;
            else if (top > first_bottom) overlap = 0;
            else if (bottom < first_top) overlap = 0;
            if (overlap) return 1;
        }
    }
    return 0;
}
asm(".align 2, 0");
