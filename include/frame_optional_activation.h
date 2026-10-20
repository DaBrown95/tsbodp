#ifndef FRAME_OPTIONAL_ACTIVATION_H
#define FRAME_OPTIONAL_ACTIVATION_H

#include "frame_optional_playback.h"
#include "frame_actor_target_jobs.h"
#include "display_actor_interaction.h"
#include "audio_game.h"

/* Adjoining, independently bounded entries. No incoming callback root is
 * established. Unused historical formals remain unresolved. */
unsigned int frame_step_optional_activation_job_82_86(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *, unsigned char);
unsigned int frame_initialize_optional_activation_context(struct FrameNeedEffectState *);
unsigned int frame_select_optional_activation_attachment_kind(struct FrameNeedEffectState *,
    unsigned char *);
unsigned int frame_begin_optional_activation_attachment_job(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_activation_attachment_job(struct FrameNeedEffectState *,
    struct FrameObject *);
unsigned int frame_step_optional_activation_job_83_84(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *, unsigned char);
unsigned int frame_step_optional_activation_job_85(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);
/* These two independent leaves consume no input. Void/unsigned-word result
 * views describe their observed effects; original unused formals are unknown. */
void frame_unrooted_optional_activation_finish_44cc8(void);
unsigned int frame_unrooted_optional_activation_value_44ccc(void);

#endif
