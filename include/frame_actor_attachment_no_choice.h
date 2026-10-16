#ifndef FRAME_ACTOR_ATTACHMENT_NO_CHOICE_H
#define FRAME_ACTOR_ATTACHMENT_NO_CHOICE_H

#include "display_actor_interaction.h"

/* Observed rows68/70/72; the E8 selector writes no action bytes. */
unsigned int frame_initialize_no_choice_attachment(struct FrameNeedEffectState *);
unsigned int frame_select_no_choice_attachment(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_begin_no_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_complete_no_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_no_choice_attachment(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_no_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_no_choice_attachment_default_value(void);

#endif
