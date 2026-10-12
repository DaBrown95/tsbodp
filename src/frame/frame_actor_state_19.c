#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"
#include "frame_actor_social.h"
#include "audio_game.h"
#include "frame_actor_actions.h"
#include "frame_actor_interaction.h"
void frame_actor_state_19(struct FrameObject *object)
{
 unsigned int finished=0;
 unsigned char index=frame_find_actor_action(((struct FrameActorActionWork *)object)->action);
 unsigned char animation=g_frame_actor_action_definitions[index].animation;
 if(((struct FrameActorActionWork *)object)->action==170) index+=((struct FrameActorActionWork *)object)->variation;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_request_animation((struct FrameCommandObject *)object,g_frame_actor_action_definitions[index].animation);
  frame_set_variant_state(object,g_frame_actor_action_definitions[index].variant);
  ((struct FrameActorActionWork *)object)->timer=g_frame_actor_action_definitions[index].duration;
  if(animation==23) {
   ((struct FrameActorActionWork *)object)->cue_handle=audio_play_animation_cue(20);
   frame_stop_motion(object);
  } else if(animation==21) {
   ((struct FrameActorActionWork *)object)->cue_handle=audio_play_animation_cue(21);
   frame_stop_motion(object);
  }
  break;
 case 59:
  frame_adjust_actor_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,g_frame_actor_action_definitions[index].need,g_frame_actor_action_definitions[index].amount);
  if(--((struct FrameActorActionWork *)object)->timer==-1) {
   if(index>20) frame_note_actor_action(((struct FrameActorActionWork *)object)->action);
   goto complete;
  }
  break;
 case 60:
  frame_adjust_actor_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,g_frame_actor_action_definitions[index].need,g_frame_actor_action_definitions[index].amount);
  if(object->flags&0x400000) finished=1;
  break;
 }
 if(finished) {
complete:
  audio_game_stop_sample(((struct FrameActorActionWork *)object)->cue_handle);
  transition_object_set_state(object,16);
  frame_set_variant_state(object,2);
  if(index==21) {
   g_actor_scene_result_id.id=0x1639;
   frame_activate_actor_scene_request();
  }
 }
}
