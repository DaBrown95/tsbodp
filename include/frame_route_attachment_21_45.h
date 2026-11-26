#ifndef FRAME_ROUTE_ATTACHMENT_21_45_H
#define FRAME_ROUTE_ATTACHMENT_21_45_H
#include "frame_need_effect_optional_jobs.h"
unsigned int frame_step_route_attachment_45_without_actor_effect(struct FrameNeedEffectState *,
                                                  struct FrameActorAttachmentRecord *);
unsigned int frame_step_route_attachment_21(struct FrameNeedEffectState *,
                                                  struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_route_attachment_21_45(struct FrameNeedEffectState *);
unsigned int frame_check_route_attachment_21_45(struct FrameNeedEffectState *,
                                                struct FrameObject *);
unsigned int frame_select_route_attachment_kinds_21_45(struct FrameNeedEffectState *, unsigned char *);
/* Unused EC formal roles remain inferred; no incoming entry is established. */
unsigned int frame_prepare_route_attachment_kinds_21_45(struct FrameNeedEffectState *,
                                                  struct FrameObject *, unsigned int);
unsigned int frame_dispatch_route_attachment_21_45(struct FrameNeedEffectState *,
                                                   struct FrameObject *);
void frame_finish_route_attachment_21_45(struct FrameNeedEffectState *);
#endif
