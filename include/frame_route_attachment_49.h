#ifndef FRAME_ROUTE_ATTACHMENT_49_H
#define FRAME_ROUTE_ATTACHMENT_49_H

struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;

/* Independently bounded worker and wrapper; incoming roots remain unknown. */
unsigned int frame_step_route_attachment_49_258c4(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_route_attachment_49_259f0(struct FrameNeedEffectState *,
    struct FrameObject *);

#endif
