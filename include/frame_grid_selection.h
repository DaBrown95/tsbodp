#ifndef FRAME_GRID_SELECTION_H
#define FRAME_GRID_SELECTION_H

#include "display_need_effect_choices.h"
#include "display_actor_interaction.h"
#include "input.h"
#include "save_world_initialization.h"
#include "frame_actor_route.h"
#include "frame_actor_idle.h"
#include "display_menu_relation_events.h"
#include "frame_need_effect_average.h"
#include "resource_conditions.h"
#include "frame_scene_actor_schedule.h"

/* Choice activation writes the actor pointer at +0x68 and phase at +0x81. */
struct FrameNeedEffectChoiceObject {
    unsigned char unknown_00[0x64];
    struct FrameNeedEffectState *owner;
    struct FrameObject *actor;
    unsigned char unknown_6c[0x15], phase;
};
extern struct FrameObject *g_grid_selected_need_effect_object;
extern const struct DisplayTimeRecord g_grid_selection_time_steps[];
unsigned char frame_need_effect_begin_choices(struct FrameObject *, struct FrameObject *);
unsigned char frame_need_effect_cycle_mode(struct FrameObject *);
void frame_need_effect_mark_attachment_running(struct FrameNeedEffectState *, struct FrameObject *);
void frame_grid_selection_interact(struct FrameObject *);
void frame_grid_selection_mark_attachments(struct FrameObject *);
void frame_step_local_need_effect_selection(void);
/* The 720-byte selection controller remains unconverted. */
void frame_update_grid_need_effect_selection(struct FrameObject *);
unsigned char frame_scene_actor_allowed(unsigned int, unsigned int, const struct DisplayTimeRecord *);
struct FrameObject *frame_create_actor(unsigned int, unsigned char, int, int);

#endif
