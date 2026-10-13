#include "frame_option_object.h"

void frame_option_tick(struct FrameObject *base)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)base;
 unsigned char direction;
 switch(object->state) {
 case 18:frame_option_action_step((struct FrameObject *)object);break;
 case 1:
  object->flags=(object->flags&~1u)|0x82;
  if(object->subtype==0) {
   register unsigned char *counter asm("r4")=(unsigned char *)&g_resource_game_state;
   counter+=0x73e;
   --*counter;
   audio_play_animation_cue(56);
   if(*counter==0)resource_set_triple(2,2,0);
  }
  break;
 default:frame_run_actor_state((struct FrameObject *)object);break;
 }
 direction=object->direction;
 if(object->pending&8)frame_refresh_velocity((struct FrameObject *)object);
 if(object->pending&4)frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[0][g_frame_actor_direction_variants[direction]]);
 if(object->pending&0x12) {
  if(object->variant==3 || object->variant==9 || object->variant==4) {
   frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[1][g_frame_actor_direction_variants[direction]]);
   frame_refresh_velocity((struct FrameObject *)object);
  } else {
   if(object->variant==5) {
    frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[2][g_frame_actor_direction_variants[direction]]);
   } else {
    frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[0][g_frame_actor_direction_variants[direction]]);
   }
   frame_stop_motion((struct FrameObject *)object);
  }
  if(direction>4)object->oam.flip_x=1;
  else object->oam.flip_x=0;
 }
 object->pending=0;
}
asm(".align 2, 0");
