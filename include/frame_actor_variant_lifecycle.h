#ifndef FRAME_ACTOR_VARIANT_LIFECYCLE_H
#define FRAME_ACTOR_VARIANT_LIFECYCLE_H

#include "frame_actor_attachment_jobs.h"

/* These entries share definition rows 10, 46, 47, 48, 94 and 103.
 * The selector remains unconverted. Its retained candidate requires a live
 * owner with one of their six
 * matching kinds and a live one-byte output. Native unmatched kinds reach
 * the adjacent parameter-rate storage; no seventh semantic variant is implied.
 * EC's unused formal roles remain provisional; its body returns one. */
unsigned int frame_initialize_variant_attachment_job(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_route_variant(struct FrameNeedEffectState *,
                                                  unsigned char *);
unsigned int frame_prepare_variant_attachment_job(struct FrameNeedEffectState *,
                                                 struct FrameObject *, unsigned int);
void frame_finish_variant_attachment_job(struct FrameNeedEffectState *);

#endif
