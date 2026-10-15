#ifndef FRAME_NEED_EFFECT_HEADER_JOBS_H
#define FRAME_NEED_EFFECT_HEADER_JOBS_H
struct FrameNeedEffectState;struct FrameObject;struct FrameActorAttachmentRecord;
unsigned int frame_begin_header_attachment_job(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_dispatch_header_attachment_job(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_step_header_attachment_job_49(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_header_attachment_job_50(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned char frame_actor_header_mode(struct FrameObject *);
/* Word ROM entries are narrowed by the actual byte direction store. */
extern const unsigned int g_header_attachment_reverse_directions[];
#endif
