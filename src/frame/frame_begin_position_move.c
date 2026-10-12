#include "frame_scene_motion.h"
void frame_begin_position_move(struct FrameObject *object,int x,int y,unsigned short duration)
{
 if(object->unknown_0a==315) object->destination.x=x-((((struct FrameSceneMotionObject*)object)->width>>1)<<16);
 else object->destination.x=x;
 object->destination.y=y;
 ((struct FrameSceneMotionObject*)object)->timer=duration;
}
