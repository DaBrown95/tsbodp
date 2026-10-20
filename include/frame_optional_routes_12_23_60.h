#ifndef FRAME_OPTIONAL_ROUTES_12_23_60_H
#define FRAME_OPTIONAL_ROUTES_12_23_60_H

#include "frame_actor_attachment_jobs_60_63.h"
#include "frame_need_effect_optional_state.h"
#include "frame_need_effect_optional_completion.h"
#include "frame_actor_target_routes.h"

unsigned int frame_initialize_optional_routes_12_23_60(struct FrameNeedEffectState *);
unsigned int frame_begin_optional_routes_12_23_60(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_routes_12_23_60(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_optional_routes_12_23_60(struct FrameNeedEffectState *);
unsigned int frame_step_optional_route_kind_60(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_route_kind_12(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_route_kind_23(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);

#endif
