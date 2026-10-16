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
unsigned int frame_begin_target_attachment_job(struct FrameNeedEffectState *,
                                                 struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_route_4(struct FrameNeedEffectState *,
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

/* Shared observed job-7 definition callbacks. */
unsigned int frame_initialize_attachment_job_7(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_7(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_7(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_job_7(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_job_7(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_7_default_value(void);

#endif
