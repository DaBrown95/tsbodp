#ifndef FRAME_ACTOR_ATTACHMENT_PALETTE_JOBS_H
#define FRAME_ACTOR_ATTACHMENT_PALETTE_JOBS_H

#include "display_actor_interaction.h"

/* Three byte selectors overlap the saved appearance record at +0x20.
 * This partial view adds only the fields actually incremented by these jobs. */
struct FrameAttachmentPaletteState {
    unsigned char unknown_00[0x24];
    unsigned char selectors[3];
};

unsigned int frame_step_attachment_palette_job_9(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_palette_jobs_8_11(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_palette_job_10(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_palette_jobs(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_palette_jobs(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_palette_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_palette_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_palette_jobs(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_palette_jobs(struct FrameNeedEffectState *);

/* Separate neighbouring entry; no installed callback role is established. */
unsigned int frame_attachment_palette_jobs_default_value(void);

#endif
