#ifndef FRAME_ACTOR_TARGET_ROUTES_H
#define FRAME_ACTOR_TARGET_ROUTES_H

struct FrameObject;
struct FramePoint;
struct FrameActorAttachmentRecord;
struct FrameNeedEffectState;
extern void *g_frame_registration;
unsigned char frame_grid_cell_to_point(void *, const int *, struct FramePoint *);
/* The neighbor search does not consume its third full-word argument. */
unsigned char frame_find_attachment_neighbor(void *, struct FrameObject *, unsigned int,
                                             unsigned char, int *);
void frame_route_attachment_to_target(void *, struct FrameActorAttachmentRecord *,
                                      struct FrameNeedEffectState *);
/* The address-derived name preserves an unresolved effect-definition role. */
unsigned int frame_interaction_step_16c68(struct FrameNeedEffectState *,
                                         struct FrameActorAttachmentRecord *);

#endif
