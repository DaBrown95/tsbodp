#ifndef FRAME_ACTOR_ROUTE_H
#define FRAME_ACTOR_ROUTE_H
/* Three 280-byte jobs; path entries occupy +0x20 through +0x10f. */
struct FrameActorRouteJob {
 struct FrameObject *object;
 struct FramePoint destination, delta;
 unsigned int *status;
 unsigned int mode, flags;
 struct FramePoint path[30];
 unsigned char path_index, unknown_111[3];
 unsigned char limit, style, use_destination, unknown_117;
};
extern struct FrameActorRouteJob g_frame_actor_routes[];
extern unsigned char g_frame_actor_route_count;
void frame_release_actor_route(unsigned char);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
struct FrameActorRouteModeDescriptor {
 unsigned char (*step)(struct FrameActorRouteJob *);
 unsigned int next;
};
extern struct FrameActorRouteModeDescriptor g_frame_actor_route_modes[];
void frame_update_actor_routes(void);
void frame_reset_actor_routes(void);
unsigned char frame_steer_actor_route(struct FrameActorRouteJob *);
unsigned char frame_find_actor_route(struct FrameActorRouteJob *);
unsigned char frame_follow_actor_route(struct FrameActorRouteJob *);
unsigned char frame_finish_actor_route(struct FrameActorRouteJob *);
#endif
