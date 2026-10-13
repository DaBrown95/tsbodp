#include "frame_option_object.h"

void frame_option_contact_interact(struct FrameObject *base,struct FrameObject *other)
{
 frame_need_effect_stop_at_position(base);
 frame_need_effect_stop_at_position(other);
 if(other->id==0 && frame_scene_effect_facing_available(other,base)) {
  frame_disable_object_flags(base,4);
  frame_set_variant_state(base,5);
  frame_request_animation((struct FrameCommandObject *)other,13);
  frame_set_variant_state(other,23);
 }
}
asm(".align 2, 0");
