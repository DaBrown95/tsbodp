#ifndef FRAME_ACTOR_SPEED_H
#define FRAME_ACTOR_SPEED_H
struct FrameObject;
struct FramePoint;
struct FrameActorSpeedProbe {unsigned char unknown00[0xac];unsigned short blocked;};
extern unsigned int g_frame_actor_speed_cue_handle;
extern unsigned char g_frame_actor_speed_cue_mode;
extern int g_frame_actor_controlled_speed;
void frame_set_actor_turn_direction(struct FrameObject *,unsigned char);
unsigned char input_rotate_direction(unsigned char,unsigned char);
void frame_actor_play_speed_cue(unsigned int,unsigned char);
void frame_actor_set_speed_cue(unsigned char);
void frame_actor_acceleration_velocity(struct FrameObject *,struct FramePoint *);
#endif
