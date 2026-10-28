#ifndef FRAME_ACTOR_DISTANCE_H
#define FRAME_ACTOR_DISTANCE_H
struct FrameObject;
struct FramePoint;
/* Selector-specific overlays, inferred from the complete movement handlers. */
struct FrameActorFollowWork {
 unsigned char unknown00[0x58]; int timer; unsigned char unknown5c[12];
 struct FrameObject *target; unsigned char unknown6c[11],wait_units,unknown78[2],range;
};
struct FrameActorFleeWork {
 unsigned char unknown00[0x5e]; unsigned short countdown; unsigned char unknown60[4];
 int saved_speed; unsigned short leave_range,enter_range,turn_delay,wait_delay;
};
unsigned int frame_point_near_any_view(int,int);
unsigned char frame_actor_terrain_step(struct FrameObject *,unsigned char);
void frame_actor_follow_target(struct FrameObject *,struct FrameObject *);
extern unsigned char g_actor_obstacle_directions[];
#endif
