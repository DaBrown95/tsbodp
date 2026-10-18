#ifndef FRAME_ACTOR_ATTACHMENT_COUNTER_CHOICES_H
#define FRAME_ACTOR_ATTACHMENT_COUNTER_CHOICES_H
#include "frame_actor_attachment_jobs.h"
#include "frame_actor_scene.h"
#include "display_need_effect_update.h"
#include "display_text_fields.h"
#include "resource_actor_selection.h"
#include "resource_commands.h"
/* Explicit original dependency; byte flag and word result from native ABI.
 * Its held candidate earns no source credit here. */
unsigned int frame_settle_actor_scene_counter(unsigned char);
unsigned int frame_initialize_counter_attachment_choices(struct FrameNeedEffectState *);
unsigned int frame_check_counter_attachment_choices(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_select_counter_attachment_choices(struct FrameNeedEffectState *,unsigned char *);
/* Unused owner/actor formal roles remain provisional. The kind is a full word. */
unsigned int frame_prepare_counter_attachment_choices(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_begin_counter_attachment_choices(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_dispatch_counter_attachment_choices(struct FrameNeedEffectState *,struct FrameObject *);
void frame_finish_counter_attachment_choices(struct FrameNeedEffectState *);
unsigned int frame_step_counter_attachment_job_19(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_counter_attachment_jobs_68_69(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
void frame_present_counter_attachment_choice(void);
void frame_remove_counter_attachment_selection(void);
#endif
