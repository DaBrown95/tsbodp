#include "display_need_effect_progress.h"
static inline struct DisplayNeedEffectProgramView *program(struct FrameNeedEffectState *state) {struct DisplayNeedEffectProgramView *table=(struct DisplayNeedEffectProgramView *)g_need_effect_programs;return &table[state->kind];}
void frame_step_need_effect_attachments(struct FrameNeedEffectState *state)
{
 struct FrameObject *object=state->object;
 unsigned int visible=object->flags&1;
 struct FrameObject **effect=(struct FrameObject **)((unsigned char *)object+0x90);
 struct FrameNeedEffectState *owner=state;
 unsigned int count=0,i;

 for(i=0;i<3;i++)if(owner->records[i].actor)count++;
 switch(state->optional) {
 case 1:
  if(!*effect) {
   if(!count&&visible==1)*effect=frame_create_actor_effect(state->object,program(state)->effect_1,program(state)->effect_2,0);
  }
  break;
 case 2:
  if(*(short *)&state->parameter>0x45ff&&! *effect&&!count&&visible==1) {
   *effect=frame_create_actor_effect(state->object,program(state)->effect_3,program(state)->effect_4,0);
  } else if(*effect&&*(short *)&state->parameter<=0x45ff) {
   transition_object_set_state(*effect,1);
   *effect=0;
  }
  break;
 case 3:
  if(!*effect&&visible==1) {
   struct FrameObject *other;
   *effect=frame_create_actor_effect(state->object,program(state)->effect_1,0,0);
   if(frame_find_objects(5,41,&other,1))(*effect)->flags&=~1;
  }
  frame_need_effect_advance_optional(state);
  break;
 default:
  if(*effect) {
   transition_object_set_state(*effect,1);
   *effect=0;
  }
 }
 if(*effect&&!visible) {
  transition_object_set_state(*effect,1);
  *effect=0;
 }
 if(((struct DisplayNeedEffectTickCallbacks *)state)->tick)((struct DisplayNeedEffectTickCallbacks *)state)->tick(state);
}
asm(".align 2, 0");
