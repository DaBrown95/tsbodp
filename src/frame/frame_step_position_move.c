#include "frame_scene_motion.h"
unsigned char frame_step_position_move(struct FrameObject *base)
{
 struct FrameSceneMotionObject *object=(struct FrameSceneMotionObject*)base;
 unsigned char done=0;
 int dx,dy;
 signed char sx,sy;
 object->timer--;
 if(object->destination.x>object->position.x) { dx=object->destination.x-object->position.x;sx=1; }
 else { dx=object->position.x-object->destination.x;sx=-1; }
 if(object->destination.y>object->position.y) { dy=object->destination.y-object->position.y;sy=1; }
 else { dy=object->position.y-object->destination.y;sy=-1; }
 if(!(dx>>16) && !(dy>>16)) {
  frame_set_velocity((struct FrameObject*)object,0,0);
  frame_set_position((struct FrameObject*)object,object->destination.x,object->destination.y);
  done=1;
 } else {
  int vx=display_bios_div(dx,object->timer)*sx;
  int vy=display_bios_div(dy,object->timer)*sy;
  frame_set_velocity((struct FrameObject*)object,vx,vy);
 }
 return done;
}
