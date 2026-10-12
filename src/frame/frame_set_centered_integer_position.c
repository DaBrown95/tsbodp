#include "frame_scene_motion.h"
void frame_set_centered_integer_position(struct FrameObject *base,short x,int y)
{
 struct FrameSceneMotionObject *object=(struct FrameSceneMotionObject*)base;
 frame_set_position(base,(x-(object->width>>1))<<16,y<<16);
}
