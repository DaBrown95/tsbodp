#ifndef FRAME_ACTOR_ATTACHMENT_DEFINITION_76_H
#define FRAME_ACTOR_ATTACHMENT_DEFINITION_76_H

#include "display_actor_interaction.h"

/* Observed definition row 76; names and unused input contracts are provisional. */
unsigned int frame_initialize_attachment_definition_76(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_definition_76(struct FrameNeedEffectState *, unsigned char *);
/* No incoming value is consumed; the generic EC caller is not identified. */
unsigned int frame_prepare_attachment_definition_76(void);
unsigned int frame_begin_attachment_definition_76(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_complete_attachment_definition_76(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_definition_76(struct FrameNeedEffectState *);

/* Separate neighbouring predicate; row 76 does not install it. */
unsigned int frame_check_attachment_definition_76(struct FrameNeedEffectState *, struct FrameObject *);

#endif
