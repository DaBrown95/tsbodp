#include "frame_animation.h"
void frame_refresh_animation_bounds(struct FrameObject *base)
{
    struct FrameAnimationObject *object = (struct FrameAnimationObject *)base;
    struct FrameAnimationState *animation = &object->animation;
    struct FrameSpriteSequence *sequence;
    if (animation->previous_frame != animation->frame || (object->flags & 0x80)) {
    sequence = animation->resource->sequence;
    if (sequence) {
        struct FrameAnimationFrame *frame = (struct FrameAnimationFrame *)
            ((FrameU8 *)sequence + 12 + sequence->frame_offsets[animation->frame]);
        struct FrameAnimationBounds *bounds = &frame->bounds;
        struct FrameCollider *collider;
        int i;
        object->bound_x1 = bounds->x;
        object->bound_x2 = (FrameU8)bounds->x + frame->width;
        object->bound_y1 = bounds->y;
        object->bound_y2 = (FrameU8)bounds->y + frame->height;
        collider = (struct FrameCollider *)((FrameU8 *)frame + 10 + sequence->attachment_count * 2);
        for (i = 0; i < sequence->collider_count; i++) {
            object->colliders[i].x = collider[i].x;
            object->colliders[i].width = collider[i].width;
            object->colliders[i].y = collider[i].y;
            object->colliders[i].height = collider[i].height;
            object->colliders[i].kind = collider[i].kind;
        }
        for (i = sequence->collider_count; i <= 1; i++)
            object->colliders[i].kind = 0;
        object->collider_count = sequence->collider_count;
    }
    if (object->sharing_flags & 0x40)
        frame_refresh_part_colliders((struct FrameObject *)object);
    object->flags |= 0x80;
    }
}
