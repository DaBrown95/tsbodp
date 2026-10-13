#ifndef FRAME_NEED_EFFECT_PLACEMENT_H
#define FRAME_NEED_EFFECT_PLACEMENT_H

#include "display_need_effect_update.h"
#include "frame_actor_state.h"

struct FrameMapRegistration;
/* Ten four-byte records are read here; the allocation's complete layout is unknown. */
struct FrameNeedEffectCell { unsigned char x,y,unknown[2]; };
struct FrameNeedEffectCells {
 unsigned char unknown[0xa4];
 struct FrameNeedEffectCell cells[10];
};
extern unsigned char *g_need_effect_action_sets[];
unsigned char frame_grid_project_effect_point(struct FrameMapRegistration *,
                                              const struct FramePoint *, unsigned int,
                                              struct FramePoint *);
unsigned char frame_need_effect_action_available(struct FrameNeedEffectState *, unsigned int);
unsigned char frame_need_effect_contains_cell(struct FrameNeedEffectState *,
                                             const struct FrameActorPackedCell *);
struct FrameNeedEffectState *frame_need_effect_find_neighbor(const struct FrameActorPackedCell *,
                                                             unsigned int);
unsigned char frame_grid_need_effect_cell_available(void *, const struct FrameActorPackedCell *,
                                                    unsigned int, unsigned char);
void frame_need_effect_pattern_cell(int, int, const unsigned char *, unsigned int,
                                    const struct FrameActorPackedCell *,
                                    struct FrameActorPackedCell *);
unsigned int frame_need_effect_pattern_dimensions(const unsigned char *,
                                                  unsigned char *, unsigned char *);
void frame_need_effect_handoff_bounds(struct FrameObject *, struct FrameNeedEffectState *,
                                      unsigned char);
void frame_need_effect_increment_counter(struct FrameNeedEffectState *,
                                         struct FrameNeedEffectState *);
void frame_need_effect_decrement_counter(struct FrameNeedEffectState *,
                                         struct FrameNeedEffectState *);
/* Direct-callee roles below remain provisional until independently reconstructed. */
unsigned char frame_need_effect_register_3b12c(void *, struct FrameObject *, unsigned char);
unsigned char frame_configure_need_effect(struct FrameObject *, int, int, int);

#endif
