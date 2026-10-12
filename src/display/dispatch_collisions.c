#include "display_collision.h"

static inline int bound_active(struct CollisionObject *object, unsigned int index)
{
    register unsigned int offset asm("r1") = index * 6;
    const signed char *types = &object->bounds[0].kind;
    return types[offset];
}
void frame_dispatch_collisions(U32 count, struct CollisionObject **objects)
{
    U8 first, first_bound, second, second_bound;
    for (first = 0; first < count - 1; first++) {
        struct CollisionObject *a = objects[first];
        for (first_bound = 0; first_bound < a->bound_count; first_bound++) {
            register int a_left asm("r9"), a_right asm("r10");
            int a_top, a_bottom;
            register int a_x asm("r0");
            register int a_y asm("r0");
            U32 a_flags;
            register int packed asm("r2");
            if (!bound_active(a, first_bound))
                continue;
            {
                struct CollisionCoordinatesView *view =
                    (struct CollisionCoordinatesView *)(first_bound * 6 + (U32)a);
                packed = view->low | ((U32)view->high << 16);
            }
            a_y = a->y;
            a_bottom = a_y + (packed >> 24);
            packed = (U32)packed << 8;
            a_top = a_y + (packed >> 24);
            packed = (U32)packed << 8;
            a_x = a->x;
            if (a->flips & 0x10) {
                a_left = a_x - (packed >> 24);
                packed = (U32)packed << 8;
                a_right = a_x - (packed >> 24);
            } else {
                a_right = a_x + (packed >> 24);
                packed = (U32)packed << 8;
                a_left = a_x + (packed >> 24);
            }
            a_flags = a->flags;
            for (second = first + 1; second < count; second++) {
                struct CollisionObject *b = objects[second];
                U32 b_flags = b->flags;
                unsigned int notified;
                unsigned int excluded = ((first_bound != 0) & ((b_flags >> 10) & 1));
                if (excluded)
                    continue;
                if ((a_flags & 0x20000) && (b_flags & 0x20000))
                    goto next_second;
                if (!(b_flags & 4))
                    goto next_second;
                notified = excluded;
                for (second_bound = 0; second_bound < b->bound_count; second_bound++) {
                    if (bound_active(b, second_bound)) {
                        int b_left, b_right, b_top, b_bottom;
                        register int b_x asm("r0");
                        register int b_y asm("r0");
                        {
                            struct CollisionCoordinatesView *view =
                                (struct CollisionCoordinatesView *)(second_bound * 6 + (U32)b);
                            packed = view->low | ((U32)view->high << 16);
                        }
                        b_y = b->y;
                        b_bottom = b_y + (packed >> 24);
                        packed = (U32)packed << 8;
                        b_top = b_y + (packed >> 24);
                        packed = (U32)packed << 8;
                        b_x = b->x;
                        if (b->flips & 0x10) {
                            b_left = b_x - (packed >> 24);
                            packed = (U32)packed << 8;
                            b_right = b_x - (packed >> 24);
                        } else {
                            b_right = b_x + (packed >> 24);
                            packed = (U32)packed << 8;
                            b_left = b_x + (packed >> 24);
                        }
                        if (a_right < b_left) goto next_bound;
                        if (a_left > b_right) goto next_bound;
                        if (a_top > b_bottom) goto next_bound;
                        if (a_bottom < b_top) goto next_bound;
                        {
                            CollisionCallback callback = a->on_collision[first_bound];
                            if (callback && !notified) {
                                callback(a, b);
                                notified = 1;
                            }
                            callback = b->on_collision[second_bound];
                            if (callback)
                                callback(b, a);
                        }
                    }
next_bound:
                    {
                        U32 flags = a->flags;
                        if (!(flags & 4)) {
                            a_flags = flags;
                            break;
                        }
                        a_flags = flags;
                        if (!(b->flags & 4) || (a_flags & 0x400))
                            break;
                    }
                }
next_second:
                if (!(a_flags & 4))
                    break;
            }
            if (!(a_flags & 4))
                break;
        }
    }
}
