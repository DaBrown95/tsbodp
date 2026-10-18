#ifndef FRAME_NEED_EFFECT_SECONDARY_HEADER_JOBS_H
#define FRAME_NEED_EFFECT_SECONDARY_HEADER_JOBS_H
#include "frame_need_effect_optional_jobs.h"
#include "frame_need_effect_header_jobs.h"
#include "frame_need_effect_header_choices.h"
#include "frame_actor_social.h"
#include "frame_actor_idle.h"
struct FrameSecondaryHeaderOwnerWork {
 unsigned char unknown00[100],active,unknown65[3];
 struct FramePoint saved_position;
};
struct FrameSecondaryHeaderActorWord {
 unsigned char unknown00[8];
 union {unsigned int word;struct {unsigned short id,subtype;} fields;} header;
};
extern const unsigned int g_secondary_header_attachment_directions_one[];
extern const unsigned int g_secondary_header_attachment_directions_two[];
unsigned int frame_begin_secondary_header_attachment_job(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_step_secondary_header_attachment_job_27(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_secondary_header_attachment_job_50(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_secondary_header_jobs(struct FrameNeedEffectState *);
unsigned int frame_select_secondary_header_attachment_jobs(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_dispatch_secondary_header_attachment_job(struct FrameNeedEffectState *,struct FrameObject *);

/* EC action switches; unused formal roles remain inferred. */
unsigned int frame_prepare_secondary_header_attachment_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

/* Observed F8 and definition+24 callbacks; incoming target domains remain open. */
void frame_tick_secondary_header_attachment_jobs(struct FrameNeedEffectState *);
unsigned char frame_secondary_header_attachment_percentage(struct FrameNeedEffectState *);

#endif
