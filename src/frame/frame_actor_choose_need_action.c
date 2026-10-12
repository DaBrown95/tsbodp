#include "frame_actor_need_actions.h"
void frame_actor_choose_need_action(struct FrameActorNeedState *state, struct FrameActorObject *object)
{
 int mask; unsigned int i;
 if (g_frame_actor_need_input.views[g_frame_actor_need_input.local_player].flags & 4) return;
 mask = frame_low_need_mask(state, 0xff);
 if (mask) {
  if (object->variant_state != 6 && (object->state == 16 || object->state == 22) && --state->countdown == -1) {
   for (i = 0; i < 8; i++) { register unsigned int bit asm("r1") = 1 << i;
    if ((mask & bit) && !(state->selected & bit)) {
     if (i == 7 && frame_need_action_forbidden(g_frame_world_id)) break;
     state->selected |= 1 << i;
     if (!(state->started & (1 << i))) {
      frame_request_animation((struct FrameCommandObject *)object, g_frame_actor_need_actions[i].animation);
      frame_set_variant_state((struct FrameObject *)object, g_frame_actor_need_actions[i].variant_state);
      object->need_timer = g_frame_actor_need_actions[i].frames;
      state->started |= 1 << i;
      if (!g_frame_actor_cue_options.variant) audio_play_animation_cue(g_frame_actor_need_actions[i].cue_zero_variant);
      else audio_play_animation_cue(g_frame_actor_need_actions[i].cue_nonzero_variant);
     }
     frame_create_actor_indicator((struct FrameObject *)object, g_frame_actor_need_actions[i].indicator, g_frame_actor_need_actions[i].frames);
     break;
    }
   }
   if (i == 8) { state->selected = 0; state->countdown = 0; }
   else state->countdown = 450;
  }
 } else { state->countdown = 0; state->selected = 0; }
 mask = frame_empty_need_mask(state);
 if (mask && (object->state == 16 || object->state == 22)) {
  if (mask & 0x20) {
   struct FrameObject *effect = frame_spawn_need_effect(135, 0, 0, 0, 1);
   *((FrameU8 *)effect + 0x83) = 1;
   if (frame_configure_need_effect(effect, 3, ((short *)&object->position)[1], ((short *)&object->position)[3]) == 1) {
    effect->flags |= 0x80000;
    ((struct FrameActorObject *)effect)->oam.layer = 3;
    frame_commit_need_effect(effect, 1);
   } else frame_remove_object(effect);
   audio_play_animation_cue(35);
   frame_set_variant_state((struct FrameObject *)object, 52);
   frame_request_animation((struct FrameCommandObject *)object, 84);
   state->countdown = 450;
  } else if (mask & 4) {
   frame_set_variant_state((struct FrameObject *)object, 53);
   frame_actor_choose_walk_direction((struct FrameObject *)object);
   frame_request_animation((struct FrameCommandObject *)object, 83);
   state->countdown = 450;
  } else if ((mask & 1) && object->variant_state != 51 && object->variant_state != 6) {
   if (!g_frame_actor_cue_options.variant) audio_play_animation_cue(128); else audio_play_animation_cue(127);
   transition_object_set_state((struct FrameObject *)object, 47);
   frame_set_variant_state((struct FrameObject *)object, 51);
   frame_request_animation((struct FrameCommandObject *)object, 82);
   state->countdown = 450;
  }
 }
}
asm(".align 2, 0");
