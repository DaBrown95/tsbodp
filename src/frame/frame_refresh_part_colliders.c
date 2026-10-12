#include "frame_animation.h"
void frame_refresh_part_colliders(struct FrameObject *base)
{
    struct FrameAnimationObject *object = (struct FrameAnimationObject *)base;
    FrameU8 part_index = 0;
    do {
        struct FrameSpriteVariant **variants = object->parts[part_index].variants;
        if (variants) {
        struct FrameAnimationObject *part_view = (struct FrameAnimationObject *)
            ((FrameU8 *)object + part_index * sizeof(struct FrameAnimationPart));
        struct FrameAnimationPart *part = &part_view->parts[0];
        if (part->flags & 2) {
            int variant = object->variant;
            int group = object->variant_group;
            struct FrameSpriteSequence *sequence =
                variants[group][variant].sequence;
            struct FrameAnimationFrame *frame;
            struct FrameCollider *colliders;
            int wrap_previous;
            int frame_index;
            int i;
            object->bound_x1 = ((FrameU8 *)sequence)[2];
            object->bound_x2 = ((FrameU8 *)sequence)[3];
            object->bound_y1 = ((FrameU8 *)sequence)[4];
            object->bound_y2 = ((FrameU8 *)sequence)[5];
            wrap_previous = (FrameU8)(part->flags & 4);
            if (wrap_previous || (part->flags & 8)) {
                frame_index = object->animation.frame - 1;
                if (frame_index < 0) {
                    if (wrap_previous)
                        frame_index = sequence->frame_count - 1;
                    else
                        frame_index = 0;
                }
            } else {
                frame_index = object->animation.frame;
            }
            frame = (struct FrameAnimationFrame *)((FrameU8 *)sequence + 12 + sequence->frame_offsets[frame_index]);
            colliders = (struct FrameCollider *)((FrameU8 *)frame + 10 + sequence->attachment_count * 2);
            for (i = 0; i < sequence->collider_count; i++) {
                if (colliders[i].kind) {
                    object->colliders[i].x = colliders[i].x;
                    object->colliders[i].width = colliders[i].width;
                    object->colliders[i].y = colliders[i].y;
                    object->colliders[i].height = colliders[i].height;
                    object->colliders[i].kind = colliders[i].kind;
                    if (object->collider_count <= i)
                        object->collider_count++;
                }
            }
        }
        }
        part_index++;
    } while (part_index <= 3);
}
asm(".align 2, 0");
