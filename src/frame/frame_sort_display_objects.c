#include "frame.h"

static inline FrameU32 priority(struct FrameObject *object)
{
    FrameU32 layer = ((((unsigned char *)object)[0xd5] << 22) & 0x03000000);
    if (object->flags & 0x80000)
        layer += 0x20000;
    else if (!(object->flags & 0x100000))
        layer += 0x10000;
    return layer;
}

static inline int pixel_y(struct FrameObject *object)
{
    return object->next_position.halves.y_pixel;
}

void frame_sort_display_objects(void)
{
    FrameU32 pass = 0x15070301;
    int count = (int)g_frame_count;
    int stop;
    struct FrameObject **objects = g_frame_objects;
    for (stop = 0; stop < count; stop++)
        if (objects[stop]->flags & 0x40000)
            break;
    do {
        int i = pass >> 24;
        int gap = i;
        FrameU32 next_pass = pass << 8;
        for (; i < stop; i++) {
            struct FrameObject *object = objects[i];
            register FrameU32 key asm("r4") = priority(object);
            int index;
            FrameU32 value;
            value = key + 0x10000;
            {
                register int y asm("r2") = pixel_y(object);
                key = value - y;
            }
            index = i;
            while (index >= gap) {
                int previous = index - gap;
                register FrameU32 other asm("r1") = priority(objects[previous]);
                register FrameU32 other_sum asm("r3") = other + 0x10000;
                register int other_y asm("r2") = pixel_y(objects[previous]);
                other = other_sum - other_y;
                value = key >= other;
                if (value)
                    break;
                objects[index] = objects[previous];
                index = previous;
            }
            objects[index] = object;
        }
        pass = next_pass;
    } while (pass);
}
