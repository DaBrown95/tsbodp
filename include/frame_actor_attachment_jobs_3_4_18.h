#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_3_4_18_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_3_4_18_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_state.h"
#include "scene.h"
/* Actual full-word mode at owner+64; a view of existing state. */
struct FrameAttachmentSequenceMode { unsigned char unknown00[0x64]; unsigned int enabled; };
unsigned int frame_step_attachment_job_18_23aa0(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_sequence_jobs_3_4(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_initialize_attachment_jobs_3_4_18(struct FrameNeedEffectState *);
unsigned int frame_check_attachment_jobs_3_4_18(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_jobs_3_4_18(struct FrameNeedEffectState *, unsigned char *);
/* EC unused firsttwo formals remain inferred until its generic consumer is known. */
unsigned int frame_prepare_attachment_jobs_3_4_18(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_3_4_18(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_3_4_18(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_attachment_jobs_3_4_18(struct FrameNeedEffectState *);
#endif
