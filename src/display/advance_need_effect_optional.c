#include "display_need_effect_progress.h"
unsigned int frame_need_effect_advance_optional(struct FrameNeedEffectState *state)
{
 struct FrameObject *player=g_need_effect_player;
 unsigned int ready=0,completed=0;
 unsigned short *parameter=&state->parameter;
 unsigned short value=*parameter;
 if(*(short *)parameter<=0x63ff) {
  *parameter=value+25;
  if(view_point_distance(state->object->position,player->position)<=0x95ffff) {
   if(((struct DisplayNeedEffectProgressObject *)state->object)->count++>89) {
    ready=frame_random_chance(frame_read_signed_parameter(g_frame_actor_social_probe,3)*2+20);
    ((struct DisplayNeedEffectProgressObject *)state->object)->count=0;
   }
  }
 } else {
  struct FrameObject *object;
  struct FramePoint point;
  transition_object_set_state(state->object,1);
  *parameter=0;
  completed=1;
  object=frame_spawn_need_effect(146,0,0,0,1);
  ((struct FrameNeedEffectObject *)object)->linked=completed;
  frame_need_effect_read_center(state->object,&point);
  if(!frame_configure_need_effect(object,3,point.x>>16,point.y>>16))frame_remove_object(object);
 }
 if(ready==1&&((struct FrameNeedEffectObject *)player)->state==16) {
  transition_object_set_state(player,47);
  frame_request_animation((struct FrameCommandObject *)player,71);
  frame_set_variant_state(player,46);
 }
 return completed;
}
asm(".align 2, 0");
