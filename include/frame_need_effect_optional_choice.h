#ifndef FRAME_NEED_EFFECT_OPTIONAL_CHOICE_H
#define FRAME_NEED_EFFECT_OPTIONAL_CHOICE_H

#include "frame_need_effect_optional_completion.h"
#include "display_need_effect_choices.h"
#include "display_need_effect_update.h"
#include "frame_actor_social.h"

/* Adjacent byte views at 0x030021F0/1/2 are distinct from the published scene
 * request/counter storage at 0x03005A00. Names describe observed reads only. */
extern unsigned char g_optional_choice_page;
extern unsigned char g_optional_choice_selection;
extern unsigned char g_optional_choice_count;
unsigned int frame_step_optional_choice_attachment_job(struct FrameNeedEffectState *,
                                                       struct FrameActorAttachmentRecord *);

/* Connected helper interfaces; broader input contracts remain provisional. */
void frame_optional_choice_begin(void);
void frame_optional_choice_open_secondary(void);
void frame_optional_choice_refresh(void);
/* Connected application interfaces. The return from completion is discarded
 * by this attachment-job caller; the provider returns the created object. */
void frame_optional_choice_apply(unsigned char, struct FrameActorAttachmentRecord *);
void frame_optional_choice_apply_special(void);
void frame_optional_choice_apply_page(unsigned char, struct FrameActorAttachmentRecord *);
struct FrameObject *frame_optional_choice_complete(unsigned int);

#endif
