#ifndef FRAME_ACTOR_TARGET_JOBS_H
#define FRAME_ACTOR_TARGET_JOBS_H

#include "frame_actor_target_routes.h"
struct FrameMapRegistration;
struct FrameActorNeedState;
/* The including subsystem supplies the shared two-word FramePoint type. */
struct FrameAttachmentEffectWork {
    unsigned char unknown00[0xcc];
    struct FramePoint first, second;
    unsigned char unknowndc[4];
    unsigned int sample;
};
unsigned char frame_grid_coordinates_to_point(struct FrameMapRegistration *,
                                               const struct FramePoint *,
                                               struct FramePoint *);
unsigned char frame_begin_target_attachment_job(struct FrameNeedEffectState *,
                                                 struct FrameObject *, unsigned int);
unsigned char frame_begin_attachment_route_4(struct FrameNeedEffectState *,
                                               struct FrameObject *, unsigned int);
unsigned char frame_begin_attachment_route_3(struct FrameNeedEffectState *,
                                               struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_49(struct FrameNeedEffectState *,
                                               struct FrameObject *);
unsigned int frame_dispatch_attachment_job_7(struct FrameNeedEffectState *,
                                              struct FrameObject *);
unsigned int frame_step_attachment_job_7(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);
unsigned char frame_direction_to_need_effect_center(struct FrameObject *,
                                                      struct FrameNeedEffectState *);
void frame_adjust_attachment_need(struct FrameActorNeedState *, unsigned int);

#endif
