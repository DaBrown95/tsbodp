#include "frame_option_object.h"

void frame_option_initialize(struct FrameObject *base)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)base;
 transition_object_set_state((struct TransitionObject *)object,9);
 frame_set_variant_state((struct FrameObject *)object,7);
 object->need_timer=60;
 frame_set_animation_record((struct FrameObject *)object,&g_frame_option_animation_sets[object->subtype].variants[0][g_frame_actor_direction_variants[object->direction]]);
 object->on_primary=g_frame_option_definitions[object->subtype].on_primary;
 object->on_secondary=g_frame_option_definitions[object->subtype].on_secondary;
 object->time1=40;object->time0=50;object->time2=90;object->time3=60;
 if(object->subtype==0) frame_acquire_palette_slot((struct FrameObject *)object,1);
 else frame_acquire_palette_slot((struct FrameObject *)object,2);
}
asm(".align 2, 0");
