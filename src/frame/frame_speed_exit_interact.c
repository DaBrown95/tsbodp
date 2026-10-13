#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_speed_exit.h"
#include "input.h"
void frame_speed_exit_interact(struct FrameObject *object,struct FrameObject *actor)
{
 unsigned int allowed,primary;
 unsigned char state=((struct FrameActorObject *)object)->state;
 struct FrameObject *selected;
 unsigned int pressed;
 allowed=0;
 if(state==0 && ((struct FrameActorObject *)actor)->state==16)allowed=1;
 selected=g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].actor;
 primary=0;
 if(actor->id==0)primary=1;
 {unsigned char *keys=(unsigned char*)g_input_pressed;unsigned int player=((struct FrameActorObject *)selected)->unknown_13;pressed=keys[player*2]&1;}
 if(primary&&pressed&&allowed) {
  input_clear();
  transition_object_set_state(object,4);
  frame_set_variant_state(object,0);
  *(struct FrameObject **)((char*)object+0x64)=actor;
 }
}
