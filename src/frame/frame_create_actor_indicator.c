#include "frame_indicator.h"
struct FrameObject *frame_create_actor_indicator(struct FrameObject *actor, int kind, int duration)
{
 FrameU16 clock=duration;
 struct FrameIndicatorObject *object=(struct FrameIndicatorObject *)frame_allocate_object(25);
 frame_set_position((struct FrameObject *)object,actor->position.x,actor->position.y);
 object->actor=actor;
 object->flags=0x100019;
 object->indicator_id=kind;
 transition_object_set_state((struct FrameObject *)object,0);
 if (clock) { object->duration=clock;object->timed=1; } else object->timed=clock;
 frame_set_animation_record((struct FrameObject *)object,&g_frame_indicator_resources[kind]);
 frame_acquire_palette_slot((struct FrameObject *)object,1);
 object->on_step=frame_indicator_tick;
 object->oam.layer=((struct FrameActorObject *)actor)->oam.layer;
 object->before_step=resource_object_before_step;
 return (struct FrameObject *)object;
}
