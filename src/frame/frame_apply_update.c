#include "frame_apply.h"
#define FRAME_SHARED ((struct FrameAllocationShared *)g_frame_shared_display)
void frame_apply_update(struct FrameApplyObject *object, FrameU8 ready)
{
    FrameU8 i;
    const void *pixels;
    struct FramePoint dimensions;
    FrameU16 bytes;
    int fresh = 1;
    FrameU16 index;
    FrameU32 flags = object->flags;
    FrameU8 sharing = object->sharing_flags;
    if (ready == 1 && (flags & 0x40000102) == 0x40000000 &&
        ((flags & 0x80) || object->index == 0xffff)) {
        frame_object_dimensions((struct FrameObject *)object, &dimensions);
        bytes = dimensions.x * dimensions.y;
        if (sharing & 3) {
            FrameU16 slot;
            if (sharing & 1) {
                struct FrameAllocationShared *shared;
                slot = 0;
                {
                    int group = object->shared_group;
                    FrameU32 base = (FrameU32)FRAME_SHARED;
                    shared = (struct FrameAllocationShared *)
                        (group * sizeof(struct FrameAllocationShared) + base);
                }
                if (!((shared->resource == object->resource && shared->counts[0] &&
                     shared->frame == object->frame) ||
                    FRAME_SHARED[object->shared_group].epoch == g_frame_allocation_epoch)) {
                    if (object->index != 0xffff) {
                        frame_free_display_range(object->index, object->bytes, object->double_tile_size);
                        object->index |= 0xffff;
                    } else {
                        FRAME_SHARED[object->shared_group].counts[slot]++;
                    }
                    FRAME_SHARED[object->shared_group].resource = object->resource;
                    index = frame_allocate_display(0, bytes, 0);
                    FRAME_SHARED[object->shared_group].frame = object->frame;
                    FRAME_SHARED[object->shared_group].indices[slot] = index;
                    FRAME_SHARED[object->shared_group].epoch = g_frame_allocation_epoch;
                } else {
                    if (object->index == 0xffff)
                        FRAME_SHARED[object->shared_group].counts[slot]++;
                    index = FRAME_SHARED[object->shared_group].indices[slot];
                    fresh = 0;
                }
            } else {
                struct FrameAllocationShared *shared;
                slot = object->frame;
                {
                    int group = object->shared_group;
                    FrameU32 base = (FrameU32)FRAME_SHARED;
                    shared = (struct FrameAllocationShared *)
                        (group * sizeof(struct FrameAllocationShared) + base);
                }
                if (!shared->counts[slot]) {
                    index = frame_allocate_display(0, bytes, 0);
                    FRAME_SHARED[object->shared_group].indices[slot] = index;
                } else {
                    index = shared->indices[slot];
                    fresh = 0;
                }
                FRAME_SHARED[object->shared_group].counts[slot]++;
                if (slot != object->previous_frame && object->index != 0xffff) {
                    FRAME_SHARED[object->shared_group].counts[object->previous_frame]--;
                    if (!FRAME_SHARED[object->shared_group].counts[object->previous_frame]) {
                        frame_free_display_range(object->index, object->bytes, object->double_tile_size);
                        object->index |= 0xffff;
                        FRAME_SHARED[object->shared_group].indices[object->previous_frame] |= 0xffff;
                    }
                }
            }
        } else {
            if (object->index != 0xffff)
                frame_free_display_range(object->index, object->bytes, object->double_tile_size);
            index = frame_allocate_display(0, bytes, 0);
            if (object->sharing_flags & 0x40) {
                for (i = 0; i < 4; i++) {
                    if (object->parts[i].variants) {
                        FrameU16 part_bytes;
                        FrameU16 part_index;
                        frame_part_dimensions((struct FrameObject *)object, &dimensions, i);
                        part_bytes = dimensions.x * dimensions.y;
                        if (object->parts[i].index != 0xffff)
                            frame_free_display_range(object->parts[i].index, object->parts[i].bytes,
                                object->double_tile_size);
                        part_index = frame_allocate_display(0, part_bytes, 0);
                        if (part_index != 0xffff) {
                            object->parts[i].index = part_index;
                            object->parts[i].bytes = part_bytes;
                        } else {
                            object->parts[i].index |= 0xffff;
                            object->parts[i].bytes = 0;
                        }
                    }
                }
            }
        }
        if (index == 0xffff) {
            fresh = 0;
            bytes = 0;
        }
        object->index = index;
        object->tile = index;
        object->bytes = bytes;
        if (fresh) {
            if (object->sharing_flags & 0x40) {
                for (i = 0; i < 4; i++) {
                    if (object->parts[i].variants && object->parts[i].index != 0xffff) {
                        FrameU8 group;
                        FrameU8 variant;
                        struct FrameSpriteSequence *sequence;
                        int wrap_previous;
                        int frame;
                        pixels = frame_part_pixels((struct FrameObject *)object, i);
                        group = object->variant_group;
                        variant = object->variant;
                        sequence = object->parts[i].variants[group][variant].sequence;
                        wrap_previous = (FrameU8)(object->parts[i].flags & 4);
                        if (wrap_previous || (object->parts[i].flags & 8)) {
                            frame = object->frame - 1;
                            if (frame < 0) {
                                if (wrap_previous)
                                    frame = sequence->frame_count - 1;
                                else
                                    frame = 0;
                            }
                        } else {
                            frame = object->frame;
                        }
                        frame_upload_sequence(object->parts[i].variants[group][variant].sequence,
                            pixels, object->parts[i].index, frame, object->parts[i].bytes);
                    }
                }
            } else {
                pixels = frame_object_pixels((struct FrameObject *)object);
                frame_upload_display((struct FrameObject *)object, pixels);
            }
        }
        object->flags |= 0x80;
    }
    object->previous_frame = object->frame;
}
asm(".align 2, 0");
