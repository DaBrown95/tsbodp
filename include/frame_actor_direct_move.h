#ifndef FRAME_ACTOR_DIRECT_MOVE_H
#define FRAME_ACTOR_DIRECT_MOVE_H
/* Saved integer target, flags, direction and resource groups for state 13. */
struct FrameActorDirectMoveWork {
 unsigned char unknown00[0x58]; int timer; unsigned char unknown5c[8];
 struct FramePoint point;
 unsigned int saved_flags;
 unsigned char saved_direction,group,index;
};
void frame_actor_step_wait_phase(struct FrameObject *);
unsigned char frame_actor_face_destination(struct FrameObject *);
void frame_set_actor_destination(struct FrameObject *,const struct FramePoint *);
void frame_unrooted_actor_waypoint_step_82bc(struct FrameObject *);
void frame_actor_choose_next_waypoint(struct FrameObject *);
unsigned char frame_unrooted_refresh_destination_velocity_2b358(struct FrameObject *);
void frame_unrooted_start_destination_move_8cd4(struct FrameObject *,int,int,int);
#endif
