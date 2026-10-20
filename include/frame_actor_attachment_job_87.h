#ifndef FRAME_ACTOR_ATTACHMENT_JOB_87_H
#define FRAME_ACTOR_ATTACHMENT_JOB_87_H

#include "frame_actor_attachment_parameters.h"
#include "frame_actor_target_jobs.h"
#include "frame_actor_social.h"

/* Bounded shared-world fields read by this job. Other bytes retain no new role. */
struct FrameAttachmentJob87World {
    unsigned char unknown_00[0x20];
    unsigned char attachment_mode;
    unsigned char unknown_21[0x77];
    unsigned int parameters[6];
};
extern struct FrameAttachmentJob87World g_attachment_job_87_world;
extern const unsigned int g_attachment_job_87_parameter_indices[6];

unsigned int frame_step_attachment_job_87(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);
unsigned int frame_begin_attachment_job_87(struct FrameNeedEffectState *,
                                           struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_87(struct FrameNeedEffectState *,
                                              struct FrameObject *);

/* Row 87's initializer and F8 tick consume no argument value.
 * Additional historical unused formals remain unresolved. */
unsigned int frame_initialize_attachment_job_87(struct FrameNeedEffectState *);
void frame_tick_attachment_job_87(struct FrameNeedEffectState *);

#endif
