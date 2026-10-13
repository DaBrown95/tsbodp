#include "frame_option_object.h"

void frame_option_configure(struct FrameObject *base)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)base;
 if(object->subtype==2 && (unsigned int)frame_read_signed_parameter(&g_frame_option_need_parameters,3)<=5 && (unsigned char)condition_group_active(3,4)==0) {
  transition_object_set_state((struct TransitionObject *)object,44);
  object->on_primary=frame_option_restricted_interact;
 } else {
  transition_object_set_state((struct TransitionObject *)object,9);
  object->on_primary=g_frame_option_definitions[object->subtype].on_primary;
  object->on_secondary=g_frame_option_definitions[object->subtype].on_secondary;
 }
 frame_set_variant_state((struct FrameObject *)object,7);
 object->need_timer=90;
 frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[0][g_frame_actor_direction_variants[object->direction]]);
 if(object->subtype==2) {object->time2=15;object->time3=45;object->time1=90;object->time0=120;}
 else {object->time2=60;object->time3=90;object->time1=50;object->time0=90;}
 object->speed=g_frame_option_definitions[object->subtype].speed;
 frame_set_subtype_object_palette((struct FrameObject *)object,g_frame_option_palettes);
}
asm(".align 2, 0");
