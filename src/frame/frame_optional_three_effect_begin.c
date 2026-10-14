#include "frame_optional_three_effect.h"

unsigned int frame_optional_three_effect_begin(struct FrameNeedEffectState *base,struct FrameObject *unused1,unsigned int unused2) {
 struct FrameOptionalThreeEffectState *state=(struct FrameOptionalThreeEffectState *)base;
 frame_optional_choice_complete(0);
 frame_commit_need_effect(state->object,3);
 state->sample_handle=audio_play_animation_cue(32);
 state->active=1;state->field65=1;
 ((struct FrameOptionalThreeEffectObject *)state->object)->timer=10;
 ((struct FrameOptionalThreeEffectObject *)state->object)->on_step=frame_optional_three_effect_tick;
 return 1;
}
asm(".align 2, 0");
