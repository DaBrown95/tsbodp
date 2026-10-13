#ifndef FRAME_NEED_EFFECT_PLACEMENT_H
#define FRAME_NEED_EFFECT_PLACEMENT_H

#include "display_need_effect_update.h"
#include "frame_actor_state.h"

/* Direct-callee roles are provisional until their bodies are reconstructed. */
unsigned char frame_need_effect_project_point_3ba54(void *, const struct FramePoint *,
                                                  unsigned char, struct FramePoint *);
unsigned char frame_need_effect_action_available_2ecc0(struct FrameNeedEffectState *,
                                                      unsigned int);
struct FrameObject *frame_need_effect_find_neighbor_2e5ec(const struct FrameActorPackedCell *,
                                                         unsigned int);
void frame_need_effect_handoff_7e68(struct FrameObject *, struct FrameObject *, unsigned char);
unsigned char frame_need_effect_register_3b12c(void *, struct FrameObject *, unsigned char);
unsigned char frame_configure_need_effect(struct FrameObject *, int, int, int);

#endif
