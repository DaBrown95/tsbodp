#include "frame_group_selector.h"

struct FrameObject *frame_create_group_selector(unsigned char group,unsigned char entry)
{
 struct FrameGroupSelectorPayload *payload=(struct FrameGroupSelectorPayload *)resource_get_object_payload(group,entry);
 struct FrameGroupSelectorObject *object=(struct FrameGroupSelectorObject *)frame_allocate_scene_object();
 if(object) {
  frame_set_position((struct FrameObject *)object,payload->x<<16,payload->y<<16);
  object->id=payload->id;
  object->subtype=payload->subtype;
  object->flags=0xe0405;
  object->object_group=payload->object_group;
  object->program_group=payload->program_group;
  object->cue=payload->cue;
  object->available=payload->available;
  object->oam.gfx_mode=0;
  object->oam.double_tile_size=0;
  object->oam.layer=3;
  frame_acquire_palette_slot((struct FrameObject *)object,g_frame_group_selector_palettes[object->subtype]);
  transition_object_set_state((struct TransitionObject *)object,0);
  object->on_step=frame_group_selector_step;
  frame_set_animation_record((struct FrameObject *)object,&g_frame_group_selector_animations[object->subtype]);
  object->on_primary=0;
  object->on_secondary=frame_group_selector_interact;
 }
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
