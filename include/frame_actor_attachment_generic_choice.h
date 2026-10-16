#ifndef FRAME_ACTOR_ATTACHMENT_GENERIC_CHOICE_H
#define FRAME_ACTOR_ATTACHMENT_GENERIC_CHOICE_H

#include "display_actor_interaction.h"

/* Shared observed rows118..148 listed in the receipt. The selector writes no
 * action bytes; its EC entry remains unowned pending an actual action producer. */
unsigned int frame_initialize_generic_choice_attachment(struct FrameNeedEffectState *);
unsigned int frame_select_generic_choice_attachment(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_begin_generic_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_complete_generic_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_generic_choice_attachment(struct FrameNeedEffectState *);

/* Separate neighbouring predicate; no installed callback role is established. */
unsigned int frame_check_generic_choice_attachment(struct FrameNeedEffectState *, struct FrameObject *);
/* Definition+24 query also installed by observed rows10/103. */
unsigned char frame_generic_choice_attachment_default_value(struct FrameNeedEffectState *);

#endif
