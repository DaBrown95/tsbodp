#ifndef FRAME_OPTIONAL_CHOICE_APPLY_H
#define FRAME_OPTIONAL_CHOICE_APPLY_H

#include "frame_optional_choice_list.h"
#include "frame_actor_scene.h"
#include "display_text_fields.h"

/* Partial game-state view. The special choice reads and decrements byte +E0;
 * its broader role and the wider allocation remain unknown. */
struct FrameOptionalChoiceBudgetWorld {
    unsigned char unknown_00[0xe0];
    unsigned char budget;
};
extern struct FrameOptionalChoiceBudgetWorld g_optional_choice_budget_world;
extern struct DisplayMenuRelationState g_display_menu_relation_state;

/* The observed stage-row stride is six signed words; arbitrary indices and
 * the number of rows have no established bound. */
extern const int g_optional_choice_costs[][6];
int frame_read_game_value(void);
int display_menu_read_relation_average(struct DisplayMenuRelationState *);
void frame_optional_choice_install_value(unsigned char);
void frame_optional_choice_apply_failure(void);

#endif
