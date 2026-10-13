#include "frame_actor_attachment_parameters.h"
struct FrameObject *frame_create_attachment_parameter_indicator(struct FrameObject *owner,unsigned int variant)
{
 struct FrameObject *object=frame_allocate_object(26);
 ((struct FrameActorObject *)object)->indicator=owner;
 frame_set_position(object,owner->position.x-0x70000,owner->position.y-0x310000);
 object->flags=0x100009;
 ((struct FrameActorObject *)object)->actor_id=variant;
 transition_object_set_state(object,0);
 frame_set_animation_record(object,&g_attachment_indicator_resources[variant]);
 frame_acquire_palette_slot(object,g_attachment_indicator_palettes[variant]);
 object->on_step=frame_attachment_parameter_indicator_tick;
 ((struct FrameActorObject *)object)->oam.layer=((struct FrameActorObject *)owner)->oam.layer;
 object->before_step=resource_object_before_step;
 return object;
}
