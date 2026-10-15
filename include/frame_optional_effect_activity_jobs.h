#ifndef FRAME_OPTIONAL_EFFECT_ACTIVITY_JOBS_H
#define FRAME_OPTIONAL_EFFECT_ACTIVITY_JOBS_H
#include "frame_need_effect_optional_jobs.h"
#include "frame_need_effect_optional_completion.h"
#include "frame_actor_social.h"
struct FrameOptionalEffectActivityWork {
 unsigned char unknown00[0x58];struct FrameObject *indicator;
 unsigned char unknown5c[8];struct FrameObject *effect;
 struct FramePoint saved_position;unsigned char unknown70[0x70];
 unsigned int sample;
};
enum FrameOptionalEffectActivityKind { FRAME_OPTIONAL_ACTIVITY_TWO=12,FRAME_OPTIONAL_ACTIVITY_INDICATOR=45,FRAME_OPTIONAL_ACTIVITY_EFFECT=53 };
unsigned int frame_optional_two_activity_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_optional_indicator_activity_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_optional_effect_activity_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_optional_effect_activity_begin(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_optional_effect_activity_dispatch(struct FrameNeedEffectState *,struct FrameObject *);
#endif
