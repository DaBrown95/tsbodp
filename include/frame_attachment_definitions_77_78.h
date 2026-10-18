#ifndef FRAME_ATTACHMENT_DEFINITIONS_77_78_H
#define FRAME_ATTACHMENT_DEFINITIONS_77_78_H

#include "display_actor_interaction.h"

/* Observed definition rows 77 and 78 share six installed callback targets.
 * This does not establish table bounds or runtime reachability. */
unsigned int frame_initialize_attachment_definitions_77_78(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_definitions_77_78(struct FrameNeedEffectState *, unsigned char *);
/* No incoming argument is consumed. The generic EC caller is unidentified;
 * this declaration does not establish the callback's historical formal roles. */
unsigned int frame_prepare_attachment_definitions_77_78(void);
unsigned int frame_begin_attachment_definitions_77_78(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
/* Calls the existing record lookup, discards its result and returns zero. */
unsigned int frame_status_attachment_definitions_77_78(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_definitions_77_78(struct FrameNeedEffectState *);

/* Separate neighbouring predicate. Neither observed row installs this entry;
 * no direct caller or raw odd-pointer reference is established. */
unsigned int frame_check_attachment_definitions_77_78(struct FrameNeedEffectState *, struct FrameObject *);

#endif
