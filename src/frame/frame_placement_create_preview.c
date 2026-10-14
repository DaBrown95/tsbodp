#include "frame_placement_session.h"
struct FrameObject *frame_placement_create_preview(struct FrameObject *base)
{
 struct FrameNeedEffectObject *source=(struct FrameNeedEffectObject *)base;
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)frame_spawn_need_effect(source->kind,0,0,0,0);
 object->position=source->position;
 object->direction=source->direction;
 frame_enable_object_flags((struct FrameObject *)object,1);
 object->linked=0;
 return (struct FrameObject *)object;
}

asm(".align 2,0");
