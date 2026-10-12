#include "frame_tick.h"
static inline void refresh_bounds(struct FrameTickObject *object)
{
    struct FrameAnimationCore *animation = (struct FrameAnimationCore *)&object->delay;
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

void frame_tick_animation(struct FrameObject *base)
{
    struct FrameTickObject *object = (struct FrameTickObject *)base;
    struct FrameAnimationCore *animation;
    if (!(object->flags & 0x10))
        return;
    animation = (struct FrameAnimationCore *)&object->delay;
    if (!animation->delay)
        return;
    if (--animation->delay)
        return;
    if (!object->commands) {
        struct FrameSpriteResource **resource;
        object->frame++;
        resource = &animation->resource;
        if (object->frame >= (*resource)->sequence->frame_count)
            object->frame = 0;
        if (object->frame == (*resource)->sequence->frame_count - 1 ||
                (*resource)->sequence->frame_count == 1)
            object->flags |= 0x400000;
        object->delay = object->frame_delay;
        refresh_bounds(object);
    } else {
        if (!(object->flags & 0x400000)) {
            object->commands += 2;
            frame_decode_animation_commands((struct FrameObject *)object);
            refresh_bounds(object);
        }
    }
}
