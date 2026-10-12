#ifndef DISPLAY_COLLISION_H
#define DISPLAY_COLLISION_H

/* Access views for the copied collision pass; names remain provisional. */
typedef unsigned char U8;
typedef unsigned int U32;
struct CollisionObject;
typedef void (*CollisionCallback)(struct CollisionObject *, struct CollisionObject *);
struct __attribute__((packed, aligned(2))) CollisionBounds {
    unsigned short low;
    short high;
    signed char kind;
    U8 unknown_05;
};
struct CollisionObject {
    U8 unknown_00[12];
    U32 flags;
    U8 unknown_10[18];
    short x;
    U8 unknown_24[2];
    short y;
    U8 unknown_28[135];
    U8 bound_count;
    struct CollisionBounds bounds[2];
    U8 unknown_bc[12];
    CollisionCallback on_collision[2];
    U8 unknown_d0[3];
    U8 flips;
};
/* Coordinate read view starts at the object's base plus a six-byte stride. */
struct CollisionCoordinatesView {
    U8 unknown_00[0xb0];
    unsigned short low;
    short high;
};
void frame_dispatch_collisions(U32 count, struct CollisionObject **objects);

#endif
