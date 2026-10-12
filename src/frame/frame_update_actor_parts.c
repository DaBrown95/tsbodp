#include "frame_actor_runtime.h"
void frame_update_actor_parts(struct FrameObject *base)
{
 struct FrameActorObject *object = (struct FrameActorObject *)base;
 frame_update_actor_movement(object->actor_state, (struct FrameObject *)object);
 if (object->pending_updates & 0x16) {
  if (object->state != 6 && (object->pending_updates & 0x12)) {
   FrameU8 variant = object->variant_state;
   if (variant == 3 || variant == 10 || variant == 13 || variant == 25 || variant == 45) {
    frame_request_animation((struct FrameCommandObject *)object, 6);
    frame_refresh_velocity((struct FrameObject *)object);
   } else if (variant == 7 || variant == 2 || variant == 11) {
    frame_request_animation((struct FrameCommandObject *)object, 1);
    frame_stop_motion((struct FrameObject *)object);
   }
  }
  if (object->pending_updates & 0x14) {
   frame_bind_actor_group((struct FrameObject *)object, g_frame_actor_definitions[object->subtype - 32]);
   frame_set_animation_variant((struct FrameObject *)object, object->requested_animation, g_frame_actor_direction_variants_signed[object->direction]);
   if (g_frame_actor_multi_kinds[object->subtype - 32][0] == 1)
    frame_set_animation_commands((struct FrameObject *)object, g_frame_actor_commands_kind1[object->requested_animation], 0);
   else frame_set_animation_commands((struct FrameObject *)object, g_frame_actor_commands_other[object->requested_animation], 0);
  }
 }
}
asm(".align 2, 0");
