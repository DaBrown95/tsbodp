#include "frame_need_effect.h"
struct FrameObject *frame_spawn_need_effect(int kind,int optional,int parameter,int mode,int enabled)
{
 FrameU8 narrow_optional=optional,narrow_parameter=parameter,narrow_mode=mode,narrow_enabled=enabled;
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)frame_allocate_object(5);
 struct FrameNeedEffectState *state;
 object->direction=3;
 object->oam.flip_x=0;
 object->requested_animation=0;
 frame_set_position((struct FrameObject *)object,0,0);
 frame_enable_object_flags((struct FrameObject *)object,0x6001c);
 if ((unsigned int)(kind-195)<=5) { object->subtype=139;object->kind=139; }
 else { object->subtype=kind;object->kind=kind; }
 transition_object_set_state((struct FrameObject *)object,0);
 object->on_remove=frame_need_effect_remove;
 if (frame_need_effect_world_option(4,5)&&object->subtype==141)
  object->on_step=frame_need_effect_special_tick;
 else object->on_step=frame_need_effect_tick;
 frame_update_actor_state((struct FrameObject *)object);
 frame_fill_bytes(object->effect_values,0,14);
 frame_fill_bytes(object->effect_choices,0,7);
 object->effect_flags=0;object->phase=0;
 state=frame_allocate_need_effect_state(object->kind);
 if(narrow_optional) state->optional=narrow_optional;
 if(narrow_parameter) state->parameter=narrow_parameter<<8;
 if(narrow_mode) state->mode=narrow_mode;
 object->effect_state=state;
 object->mode=0;object->linked=0;
 state->object=(struct FrameObject *)object;
 state->kind=object->subtype;
 state->enabled=narrow_enabled;
 if(state&&g_frame_need_effect_definitions[object->kind].callback)
  frame_need_effect_initialize(state,g_frame_need_effect_definitions[object->kind].callback);
 if(kind==135)object->oam.layer=3;
 frame_update_need_effect((struct FrameObject *)object);
 if(kind==135){object->sharing_flags|=0x20;object->parts[0].flags|=1;}
 object->before_step=frame_need_effect_before_step;
 return (struct FrameObject *)object;
}
