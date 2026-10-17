#ifndef FRAME_SCENE_MOTION_H
#define FRAME_SCENE_MOTION_H
#include "frame_scene_object.h"
struct FrameSceneMotionObject {
 unsigned char unknown_00[8]; unsigned short id, subtype;
 unsigned int flags; unsigned char unknown_10[8];
 struct FramePoint position,next_position,velocity,acceleration,destination;
 unsigned char unknown_40[13]; unsigned char state,variant;
 unsigned char unknown_4f[15]; unsigned short timer;
 unsigned char unknown_60[120]; unsigned short width;
};
void frame_begin_position_move(struct FrameObject *,int,int,unsigned short);
unsigned char frame_step_position_move(struct FrameObject *);
void frame_set_centered_integer_position(struct FrameObject *,short,int);
void frame_set_velocity(struct FrameObject *,int,int);
void frame_set_oriented_velocity_x(struct FrameObject *,int);
void frame_set_oriented_velocity_y(struct FrameObject *,int);
int display_bios_div(int,int);
#endif
