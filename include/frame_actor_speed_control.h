#ifndef FRAME_ACTOR_SPEED_CONTROL_H
#define FRAME_ACTOR_SPEED_CONTROL_H
#include "frame_actor_speed.h"
#include "frame_transient_effect.h"
struct FrameActorSpeedGame {unsigned char unknown00[0x424];struct FramePoint saved_position;unsigned char world,unknown42d,exit_flag,resume;};
extern struct FrameTransientEffect *g_frame_actor_speed_effect;
extern unsigned int g_frame_actor_speed_frames,g_frame_actor_restart_cue;
extern unsigned char g_frame_actor_turn_timer,g_frame_actor_control_mode,g_frame_actor_turn_ready,g_frame_actor_restart_ready;
struct FrameObject *frame_create_speed_exit_actor(unsigned char,int,int);
#endif
