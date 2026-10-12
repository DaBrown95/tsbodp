#ifndef FRAME_ACTOR_ROUTE_H
#define FRAME_ACTOR_ROUTE_H
/* Three 280-byte jobs; opaque route scratch occupies +0x20 through +0x113. */
struct FrameActorRouteJob {
 struct FrameObject *object;
 struct FramePoint destination, delta;
 unsigned int *status;
 unsigned int mode, flags;
 unsigned char unknown_20[244];
 unsigned char limit, style, use_destination, unknown_117;
};
extern struct FrameActorRouteJob g_frame_actor_routes[];
extern unsigned char g_frame_actor_route_count;
void frame_release_actor_route(unsigned char);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
#endif
