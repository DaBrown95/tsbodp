#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_interaction.h"
#include "input.h"
#include "view_math.h"
#include "audio_game.h"
#include "frame_actor_carry.h"
void frame_actor_state_42(struct FrameObject *object)
{
 struct FramePoint attachment,velocity;
 struct FramePoint *out;
 unsigned int player=((struct FrameActorObject *)object)->unknown_13;
 unsigned int idle;
 unsigned char mode,input;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 65:
  object->velocity.x=0;object->velocity.y=0;
  ((struct FrameActorObject *)object)->direction=1;
  ((struct FrameActorCarryWork *)object)->timer=17;
  if(object->flags&0x400000) {
   frame_set_variant_state(object,67);
   frame_read_attachment(object,0,&attachment);
   ((struct FrameActorCarryWork *)object)->x=(object->position.x>>16)+attachment.x;
   ((struct FrameActorCarryWork *)object)->y=(object->position.y>>16)+attachment.y;
   ((struct FrameActorCarryWork *)object)->align=1;
  }
  break;
 case 66:
  object->velocity.x=0;object->velocity.y=0;
  ((struct FrameActorObject *)object)->direction=3;
  if(object->flags&0x400000) {
   transition_object_set_state(object,16);
   frame_set_variant_state(object,2);
   frame_read_attachment(object,0,&attachment);
   object->position.x+=attachment.x<<16;
   object->position.y+=attachment.y<<16;
  }
  break;
 case 67:
  if(++((struct FrameActorCarryWork *)object)->timer==19) {
   audio_play_animation_cue(30);
   ((struct FrameActorCarryWork *)object)->timer=0;
  }
  if(((struct FrameActorCarryWork *)object)->align) {
   struct FrameObject *effect;
   object->position.x=((struct FrameActorCarryWork *)object)->x<<16;
   object->position.y=((struct FrameActorCarryWork *)object)->y<<16;
   ((struct FrameActorCarryWork *)object)->align=0;
   effect=frame_create_actor_effect(object,200,3,1);
   transition_object_set_state(effect,5);
   effect->position.x=object->position.x;effect->position.y=object->position.y;
  }
  idle=0;
  {
   input=input_direction(player);
   if(input!=8)frame_set_actor_direction(object,input);
   else idle=1;
  }
  if(idle==0) {
   unsigned int fast; register unsigned int flags asm("r4"); unsigned char direction; int speed;
   fast=g_input_current[g_frame_actor_need_input.local_player]&2;
   out=&velocity;
   if(fast) {
    flags=object->flags; direction=((struct FrameActorObject *)object)->direction;
    speed=(int)(unsigned int)(((struct FrameActorObject *)object)->speed*1.1);
   } else {
    flags=object->flags; direction=((struct FrameActorObject *)object)->direction;
    speed=(int)(unsigned int)(((struct FrameActorObject *)object)->speed*0.6);
   }
   frame_make_velocity(out,flags,direction,speed);
   frame_request_animation((struct FrameCommandObject *)object,55);
  } else {
   frame_set_variant_state(object,68);
   frame_request_animation((struct FrameCommandObject *)object,55);
   velocity.x=0;velocity.y=0;out=&velocity;
  }
  object->velocity.x=velocity.x;object->velocity.y=out->y;
  frame_handle_actor_empty_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,(struct FrameActorObject *)object);
  frame_adjust_actor_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,50,1);
  break;
 case 68:
  idle=1;velocity.x=0;velocity.y=0;
  ((struct FrameActorCarryWork *)object)->timer=17;
  mode=g_resource_view_effects[player].mode;
  out=&velocity;
  if(mode!=1) {
   input=input_direction(player);
   if(input!=8) {
    frame_set_actor_direction(object,input_direction(player));
    idle=0;
   }
   if(idle==0) {
    if(g_input_current[g_frame_actor_need_input.local_player]&2) {
     frame_make_velocity(out,object->flags,((struct FrameActorObject *)object)->direction,(int)(unsigned int)(((struct FrameActorObject *)object)->speed*1.1));
     frame_request_animation((struct FrameCommandObject *)object,55);
    } else {
     frame_make_velocity(out,object->flags,((struct FrameActorObject *)object)->direction,(int)(unsigned int)(((struct FrameActorObject *)object)->speed*0.6));
     frame_request_animation((struct FrameCommandObject *)object,55);
    }
    frame_set_variant_state(object,67);
   } else frame_request_animation((struct FrameCommandObject *)object,55);
  } else frame_request_animation((struct FrameCommandObject *)object,55);
  object->velocity.x=velocity.x;object->velocity.y=out->y;
  frame_handle_actor_empty_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,(struct FrameActorObject *)object);
  frame_adjust_actor_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,50,1);
  break;
 case 0:break;
 }
}
