#ifndef FRAME_NEED_EFFECT_OPTIONAL_SELECTION_H
#define FRAME_NEED_EFFECT_OPTIONAL_SELECTION_H

#include "frame_need_effect_optional_jobs.h"
#include "display_time.h"

extern struct DisplayTimeRecord g_display_world_clock;
unsigned int frame_need_effect_optional_two_ready(struct FrameNeedEffectState *, int);
/* These callbacks write attachment-kind bytes; output capacity is unestablished. */
unsigned int frame_select_optional_attachment_kinds_1a38c(struct FrameNeedEffectState *,
                                                         unsigned char *);
unsigned int frame_select_optional_attachment_kinds_28764(struct FrameNeedEffectState *,
                                                         unsigned char *);
unsigned int frame_select_optional_attachment_kinds_35c3c(struct FrameNeedEffectState *,
                                                         unsigned char *);
unsigned int frame_select_optional_attachment_kinds_3a994(struct FrameNeedEffectState *,
                                                         unsigned char *);
unsigned int frame_select_optional_attachment_kinds_46200(struct FrameNeedEffectState *,
                                                         unsigned char *);


/* EC action switches; unused formal roles remain inferred. */
unsigned int frame_prepare_optional_attachment_kinds_12_23_60(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_prepare_optional_attachment_kinds_12_45_53(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_prepare_optional_attachment_kinds_12_45_59(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_prepare_optional_attachment_kinds_12_31_33_45(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

#endif
