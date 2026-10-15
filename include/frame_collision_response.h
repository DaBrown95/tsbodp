#ifndef FRAME_COLLISION_RESPONSE_H
#define FRAME_COLLISION_RESPONSE_H
#include "frame.h"
#include "display_collision.h"
#include "view_math.h"

/* Partial fixed-ABI access views. These do not establish allocation capacity. */
struct FrameCollisionMotion {
 unsigned char unknown00[18],direction,unknown13;
 int speed;
};
struct FrameCollisionContactState {
 unsigned char unknown00[172];
 unsigned short contact;
};
struct FrameCollisionRadius {
 unsigned char unknown00[174],radius;
};
void frame_add_points(const struct FramePoint *,const struct FramePoint *,struct FramePoint *);

/* The sampled second-object direction must be 0..7. The native default path
 * leaves its sample coordinates unwritten. Global reachability of that path
 * is unresolved; the source fixtures also bound signed arithmetic. */
void frame_resolve_actor_contact(struct FrameObject *,struct FrameObject *);
void frame_scene_player_collision(struct CollisionObject *,struct CollisionObject *);
#endif
