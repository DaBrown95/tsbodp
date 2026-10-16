#include "frame_actor_runtime.h"
#include "audio_game.h"
#include "frame_actor_effect.h"
struct FrameObject *frame_create_actor_effect(struct FrameObject *owner,unsigned char attachment,unsigned int kind,unsigned char completion_mode)
{
 struct FramePoint position;
 struct FrameActorEffectObject *object;
 if(kind==10)return 0;
 object=(struct FrameActorEffectObject *)frame_allocate_object(28);
 if(!object)return 0;
 if(frame_attachment_position(owner,attachment,&position)==1)
  frame_set_position((struct FrameObject *)object,position.x,position.y);
 else frame_set_position((struct FrameObject *)object,owner->position.x,owner->position.y);
 object->before_step=0;
 ((struct FrameObject *)object)->spatial.bounds.lower.x=((struct FrameObject *)object)->spatial.bounds.upper.x=owner->spatial.bounds.upper.x-1;
 ((struct FrameObject *)object)->spatial.bounds.lower.y=((struct FrameObject *)object)->spatial.bounds.upper.y=owner->spatial.bounds.upper.y+1;
 object->flags=0x40011;
 object->subtype=kind;object->kind=kind;object->owner=owner;object->completion_mode=completion_mode;
 transition_object_set_state((struct FrameObject *)object,0);
 frame_set_animation_record((struct FrameObject *)object,&g_frame_actor_effect_resources[kind]);
 frame_acquire_palette_slot((struct FrameObject *)object,g_frame_actor_effect_palettes[kind]);
 object->on_step=frame_actor_effect_tick;
 object->oam.layer=((struct FrameActorObject *)owner)->oam.layer;
 switch(kind) { case 1:case 2:case 3:case 4:object->sharing_flags|=0x20; break; }
 if(g_frame_actor_effect_cues[kind]<=229)object->cue_handle=audio_play_animation_cue(g_frame_actor_effect_cues[kind]);
 return (struct FrameObject *)object;
}
