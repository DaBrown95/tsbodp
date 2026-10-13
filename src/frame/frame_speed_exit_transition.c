#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"
#include "frame_actor_speed_exit.h"
void frame_speed_exit_transition(struct FrameObject *object)
{
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  g_actor_scene_request.active=0;
  g_actor_scene_result_id.id=g_actor_exit_scene_defaults[0];
  ((unsigned short*)&g_actor_scene_result_id)[1]=g_actor_exit_scene_defaults[1];
  ((unsigned char*)&g_actor_scene_request)[1]=0;
  ((unsigned char*)&g_actor_scene_request)[2]=0;
  display_scene_stage_08027dc0(2);
  frame_set_variant_state(object,55);
  break;
 case 55:
  {int result=((struct FrameSpeedExitSceneResult *)&g_resource_scene_arg)->result;
   if(result!=-1) {
   if(result==0) {
    struct FrameObject *actor=*(struct FrameObject **)((char*)object+0x64);
    transition_object_set_state(actor,27);
    frame_set_variant_state(*(struct FrameObject **)((char*)object+0x64),0);
    frame_set_actor_direction(*(struct FrameObject **)((char*)object+0x64),((struct FrameActorObject *)object)->direction);
    ((struct FrameActorSpeedGame *)&g_resource_game_state)->exit_flag=1;
    transition_object_set_state(object,1);
    frame_enable_object_flags(object,2);
   } else if(result==1) {
    unsigned char direction=frame_direction_toward(*(struct FrameObject **)((char*)object+0x64),object);
    frame_set_actor_direction(*(struct FrameObject **)((char*)object+0x64),direction);
    frame_request_animation((struct FrameCommandObject *)*(struct FrameObject **)((char*)object+0x64),28);
    frame_set_variant_state(*(struct FrameObject **)((char*)object+0x64),75);
    ((struct FrameActorStateWork *)*(struct FrameObject **)((char*)object+0x64))->timer=90;
    transition_object_set_state(object,0);
    frame_set_variant_state(object,7);
   }
   } else {transition_object_set_state(object,0);frame_set_variant_state(object,7);}
  }
  break;
 }
}
asm(".align 2, 0");
