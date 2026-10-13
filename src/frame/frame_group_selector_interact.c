#include "frame_group_selector.h"

void frame_group_selector_interact(struct FrameObject *base,struct FrameObject *other)
{
 struct FrameGroupSelectorObject *object=(struct FrameGroupSelectorObject *)base;
 struct FrameGroupSelectorObject *actor=(struct FrameGroupSelectorObject *)other;
 if(actor->id!=0 || actor->state!=16 || object->available!=1) return;
 audio_play_animation_cue(object->cue);
 frame_set_animation_frame((struct FrameTickObject *)object,1);
 resource_activate_groups(object->object_group,object->program_group);
 object->available=0;
 input_clear();
}
asm(".align 2, 0");
