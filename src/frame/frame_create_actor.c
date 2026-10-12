#include "frame_actor_runtime.h"
struct FrameObject *frame_create_actor(FrameU32 actor_id, FrameU8 direction, int x, int y)
{
 struct FrameActorObject *object = (struct FrameActorObject *)frame_allocate_object(7);
 frame_set_position((struct FrameObject *)object, x, y);
 object->id = 7;
 object->subtype = actor_id;
 object->actor_id = actor_id;
 object->unknown_50 = 0;
 object->direction = direction;
 object->speed = g_frame_actor_speeds[object->subtype];
 object->flags = 0x1005045d;
 object->before_step = resource_object_before_step;
 frame_install_actor_script((struct FrameObject *)object, g_frame_actor_script);
 if (object->subtype > 31) {
  frame_enable_parts((struct FrameObject *)object);
  frame_request_animation((struct FrameCommandObject *)object, 1);
  frame_bind_actor_group((struct FrameObject *)object, g_frame_actor_definitions[object->subtype - 32]);
  frame_set_animation_variant((struct FrameObject *)object, object->requested_animation,
   g_frame_actor_direction_variants_signed[object->direction]);
  frame_set_part_order((struct FrameObject *)object, 0, 4);
  frame_set_part_order((struct FrameObject *)object, 1, 5);
  frame_set_part_order((struct FrameObject *)object, 2, 6);
  frame_load_actor_group_palette(g_frame_actor_definitions[object->subtype - 32], object->oam.palette);
 } else {
  if (object->subtype == 25) {
   frame_set_animation_record((struct FrameObject *)object,
    g_frame_actor_animation_sets[object->subtype][2].variants + g_frame_actor_direction_variants[object->direction]);
   object->sharing_flags |= 0x20;
  } else {
   frame_set_animation_record((struct FrameObject *)object,
    g_frame_actor_animation_sets[object->subtype][1].variants + g_frame_actor_direction_variants[object->direction]);
  }
 }
 object->on_step = frame_actor_tick;
 object->on_remove = frame_actor_remove;
 if ((FrameU16)(object->subtype - 6) <= 11)
  object->on_interact = frame_actor_interaction_special;
 else if (object->subtype > 17)
  object->on_interact = frame_actor_interaction_default;
 frame_update_actor_state((struct FrameObject *)object);
 if (actor_id > 31)
  object->actor_state = frame_initialize_actor_state(actor_id);
 else object->actor_state = 0;
 if (actor_id <= 5) {
  object->default_state = g_frame_actor_default_states[actor_id];
  object->reset = 0;
  frame_refresh_interaction_choices();
 } else {
  if (g_frame_world_id == 31 && object->subtype == 19) {
   object->default_state = 36;
   object->on_interact = frame_actor_interaction_world31;
  } else if (object->subtype == 25) object->default_state = 41;
  else object->default_state = 35;
 }
 transition_object_set_state((struct FrameObject *)object, object->default_state);
 frame_set_variant_state((struct FrameObject *)object, 2);
 if (object->direction > 4) object->oam.flip_x = 1;
 else object->oam.flip_x = 0;
 frame_actor_note_spawn(object->subtype);
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
