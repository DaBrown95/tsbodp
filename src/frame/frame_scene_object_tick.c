#include "frame_scene_motion.h"
void frame_scene_object_tick(struct FrameObject *object)
{
 unsigned short id=object->id;
 switch(((struct FrameActorObject*)object)->state) {
 case 14:
  switch(((struct FrameActorObject*)object)->variant_state) {
  case 0:
   frame_set_position(object,g_frame_scene_positions[id].x0<<16,g_frame_scene_positions[id].y0<<16);
   frame_set_variant_state(object,11);
   break;
  case 56:
   if(object->unknown_0a!=315) frame_set_position(object,g_frame_scene_positions[id].x0<<16,g_frame_scene_positions[id].y0<<16);
   else frame_set_centered_integer_position(object,g_frame_scene_positions[id].x0,g_frame_scene_positions[id].y0);
   frame_begin_position_move(object,g_frame_scene_positions[id].x1<<16,g_frame_scene_positions[id].y1<<16,((struct FrameSceneMotionObject*)object)->timer+1);
   frame_step_position_move(object);
   frame_set_variant_state(object,3);
   object->flags|=1;
   break;
  case 3:
   if(frame_step_position_move(object)==1) frame_set_variant_state(object,11);
   break;
  case 57:
   if(object->unknown_0a!=315) frame_set_position(object,g_frame_scene_positions[id].x1<<16,g_frame_scene_positions[id].y1<<16);
   else frame_set_centered_integer_position(object,g_frame_scene_positions[id].x1,g_frame_scene_positions[id].y1);
   frame_begin_position_move(object,g_frame_scene_positions[id].x0<<16,g_frame_scene_positions[id].y0<<16,((struct FrameSceneMotionObject*)object)->timer);
   frame_step_position_move(object);
   frame_set_variant_state(object,3);
   object->flags|=1;
   break;
  case 1:
  case 2:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
  case 30:
  case 31:
  case 32:
  case 33:
  case 34:
  case 35:
  case 36:
  case 37:
  case 38:
  case 39:
  case 40:
  case 41:
  case 42:
  case 43:
  case 44:
  case 45:
  case 46:
  case 47:
  case 48:
  case 49:
  case 50:
  case 51:
  case 52:
  case 53:
  case 54:
  case 55:break;
  case 58:
   frame_set_position(object,g_frame_scene_positions[id].x1<<16,g_frame_scene_positions[id].y1<<16);
   frame_set_variant_state(object,11);
   break;
  }
  break;
 case 8:
  if(!((struct FrameActorObject*)object)->variant_state) frame_set_variant_state(object,11);
  break;
 }
}
