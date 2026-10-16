#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_16_17_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_16_17_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"
#include "resource_condition_entries.h"
/* One access view of existing canonical game state. The pending record is
 * read as an aligned word and also through its actual byte members. */
union FrameAttachmentPendingEntry {
    unsigned int word;
    struct { unsigned char timer, kind, active, unknown03; } bytes;
};
struct FrameAttachmentSelectionWorld {
    unsigned char unknown00[0xf4];
    struct ConditionActorEntries *entries;
    unsigned char unknownf8[0x43c-0xf8];
    union FrameAttachmentPendingEntry pending;
    unsigned char unknown440[0x746-0x440], selected;
};
unsigned int frame_initialize_attachment_jobs_16_17(struct FrameNeedEffectState *);
unsigned int frame_check_attachment_jobs_16_17(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_select_attachment_jobs_16_17(struct FrameNeedEffectState *,unsigned char *);
/* Unused EC formal roles remain inferred until its generic consumer is known. */
unsigned int frame_prepare_attachment_jobs_16_17(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_begin_attachment_jobs_16_17(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_dispatch_attachment_jobs_16_17(struct FrameNeedEffectState *,struct FrameObject *);
void frame_tick_attachment_jobs_16_17(struct FrameNeedEffectState *);
/* Independent neighbouring entry; row133's FC pointer is null. */
unsigned int frame_attachment_jobs_16_17_default_value(void);
unsigned int frame_step_attachment_job_16_2bccc(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_17_2bd38(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
#endif
