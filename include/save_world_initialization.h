#ifndef SAVE_WORLD_INITIALIZATION_H
#define SAVE_WORLD_INITIALIZATION_H
#include "save_game_serialization.h"
#include "resource_conditions.h"
#include "display_menu_relation_events.h"
#include "display_window_motion.h"
#include "display_text_runtime.h"
#include "heap.h"

struct ActorEntryContext;
struct FrameActorNeedState;
struct FrameObject;
/* A reset at world +440 clears 724 bytes, then restores this first word. */
struct SaveWorldConditionBlock {
    unsigned int selected;
    unsigned char unknown04[720];
};
struct SaveWorldConditionSource {
    unsigned char unknown00[0x440];
    unsigned int row;
};
/* Same 56-byte rows as the clock/save views. The observed object array is eight
 * nullable slots; the complete row roles and incoming row bounds are unknown. */
struct SaveWorldTransitionRow {
    unsigned int ready, flags;
    unsigned short ticks;
    unsigned char unknown0a[6];
    struct FrameObject *objects[8];
    unsigned char unknown30[8];
};
/* Partial view through +752. Pending shares the countdown used by the clock;
 * these offsets establish no complete game-state allocation or value domain. */
struct SaveWorldInitState {
    struct SaveStreamGameStateView prefix;
    int pending;
    unsigned char unknown750, pending_row, pending_columns;
};
extern struct SaveWorldConditionBlock g_save_world_condition_block;
extern struct SaveWorldConditionSource g_save_world_condition_source;
extern struct SaveWorldTransitionRow g_save_world_transition_rows[];
extern struct SaveWorldInitState g_save_world_init_state;
extern const struct DisplayTimeRecord g_save_default_clock;

void save_world_initialize(void);
/* Record reset also writes the 44-byte need state at +A0, through +CB. The
 * separately serialized +A0 child covers only its eight value words. */
void save_world_initialize_record(void *);
void save_world_initialize_relations(struct DisplayMenuRelationState *);
void save_world_initialize_conditions(void);
void save_world_reset_transition_row(unsigned int);
void save_world_begin_transition(unsigned int);
unsigned int save_world_transition_ready(unsigned int);
void save_world_clear_row_objects(void);
/* This direct helper requires a non-null slot; it retains unchecked byte index. */
void save_world_release_row_object(struct SaveWorldTransitionRow *, unsigned char);

void actor_entry_reset(struct ActorEntryContext *);
void frame_reset_actor_needs(struct FrameActorNeedState *);
void resource_set_display_kind(unsigned int);
unsigned int audio_play_animation_cue(unsigned int);
/* Original no-op hooks remain explicit unconverted calls. */
void save_world_empty_hook_32000(void *);
void save_world_empty_hook_3d170(void *);
#endif
