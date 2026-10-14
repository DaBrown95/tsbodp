#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "audio_game.h"
#include "input.h"
#include "frame_actor_social.h"
#include "frame_actor_interaction.h"
void frame_actor_state_22(struct FrameObject *object)
{
 unsigned int finished=0,special=0;
 unsigned int player=((struct FrameActorObject *)object)->unknown_13;
 unsigned char direction=input_direction(player);
 unsigned int reset_animation=1;
 struct FrameInteractionOption *entry;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_request_animation((struct FrameCommandObject *)object,49);
  if(((struct FrameActorInteractionWork *)object)->mode==1) {
   entry=&((struct FrameInteractionWorld *)&g_resource_game_state)->options->entries[((struct FrameActorInteractionWork *)object)->option_index];
   ((struct FrameActorInteractionWork *)object)->effect=frame_spawn_need_effect(entry->id,entry->field1,entry->field2,entry->field3,1);
  }
  frame_enable_object_flags(((struct FrameActorInteractionWork *)object)->effect,1);
  frame_placement_begin(g_frame_registration,object,((struct FrameActorInteractionWork *)object)->effect);
  frame_set_variant_state(object,18);
  frame_stop_motion(object);
  break;
 case 18:
  if((g_input_pressed[player]&2) || (frame_empty_need_mask((struct FrameActorNeedState *)&g_frame_actor_local_need_state)&0x25)) {
   frame_placement_cancel();
   audio_play_animation_cue(2);
   finished=1;
   g_input_pressed[player]&=0xfffd;
   break;
  }
  if(g_input_pressed[player]&1) {
   if(frame_placement_confirm()==1) {
    if(((struct FrameActorInteractionWork *)object)->mode==1) {
     entry=&g_frame_actor_local_need_state.options->entries[((struct FrameActorInteractionWork *)object)->option_index];
     frame_note_interaction_condition(entry->id);
     if((unsigned char)(entry->id+61)<=5) g_frame_actor_local_need_state.selected_world=g_frame_world_id;
     if(g_frame_interaction_definitions[entry->id].special==1) special=1;
     if(entry->id==141 && g_frame_world_id==9) resource_set_triple(4,5,3);
     if(((struct FrameActorInteractionWork *)object)->mode==1)
      condition_update_actor((struct ConditionActorEntries *)((struct FrameInteractionWorld *)&g_resource_game_state)->options,((struct FrameActorInteractionWork *)object)->option_index,1);
    }
    audio_play_animation_cue(1); finished=1;
   } else audio_play_animation_cue(3);
   g_input_pressed[player]&=0xfffe;
   break;
  }
  if(g_input_pressed[player]&0x100) {
   frame_placement_rotate(0); audio_play_animation_cue(10);
  } else if(g_input_pressed[player]&0x200) {
   frame_placement_rotate(1); audio_play_animation_cue(10);
  } else if(direction!=8) {
   direction=g_frame_interaction_directions[direction];
   frame_placement_move(direction);
   audio_play_animation_cue(0);
   frame_set_variant_state(object,11);
  } else frame_placement_validate();
  break;
 case 11:
  if(input_direction(player)==8) frame_set_variant_state(object,18);
  break;
 default:
  frame_placement_cancel();reset_animation=0;finished=1;
 }
 if(finished==1) {
  transition_object_set_state(object,16);
  if(special==1) {
   frame_request_animation((struct FrameCommandObject *)object,67);
   frame_set_variant_state(object,74);
   audio_play_animation_cue(27);
  } else if(reset_animation==1) {
   frame_request_animation((struct FrameCommandObject *)object,1);
   frame_set_variant_state(object,2);
  }
 }
}
