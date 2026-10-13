#include "display_need_effect_update.h"
#include "scene.h"
void frame_need_effect_restore_audio(struct FrameObject *object)
{
 struct FrameNeedEffectState *state=((struct FrameNeedEffectObject *)object)->effect_state;
 unsigned int kind=state->kind;
 if(state->optional!=1 && (kind==44||kind==45||kind==42||kind==43||kind==49||kind==104)) {
  short *parameter=(short *)&state->parameter;
  if(*parameter!=0) {
   audio_select_sequence(scene_resource_audio_id(g_scene_context.resource));
   *parameter=0;
  }
 }
}
asm(".align 2, 0");
