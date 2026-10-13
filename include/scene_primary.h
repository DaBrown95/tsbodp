#ifndef SCENE_PRIMARY_H
#define SCENE_PRIMARY_H
#include "frame_scene_player.h"
#include "scene_request.h"
#include "resource_view_effects.h"
#include "audio_vblank.h"

/* Access view of four 12-byte slots and their shared count/selection bytes. */
struct ScenePrimarySlot {
    struct FrameActorObject *object;
    unsigned short flags;
    unsigned char unknown_06, saved_direction;
    short saved_x, saved_y;
};
struct ScenePrimaryViews {
    struct ScenePrimarySlot slots[4];
    unsigned char count, current_view;
};
/* Same 56-byte stride as existing need/UI records; unnamed bytes stay unknown. */
struct ScenePrimaryViewFlags {
    unsigned int unknown_00, flags;
    unsigned char unknown_08[48];
};
struct ScenePrimaryViewChanges {
    unsigned int changed;
    unsigned char unknown_04[52];
};
struct ScenePrimaryGameSelection {
    unsigned char unknown_00[0x73f], requested_kind;
};
extern struct ScenePrimaryViews g_scene_primary_views;
extern struct ScenePrimaryViewFlags g_scene_primary_view_flags[];
extern struct ScenePrimaryViewChanges g_scene_primary_view_changes[];
extern struct ScenePrimaryGameSelection g_scene_primary_game_selection;
extern unsigned short g_input_pressed[];
extern unsigned int g_game_flags, g_scene_id;
extern struct FrameObjectList g_frame_primary_list;
extern void *g_frame_registration;
extern unsigned char g_scene_entry_data[];

void scene_primary_step(void), scene_primary_exit(void);
void frame_update_map_view(unsigned char), frame_step_transient_effects(void);
void scene_step_character_animation(void), scene_submit_default_request(unsigned int);
unsigned char scene_request_changed(void);
unsigned int scene_queued_request_kind(void), audio_play_animation_cue(unsigned int);
void transition_fade_black_out_record(unsigned short);
void transition_run_second(unsigned short, unsigned int);
void display_release_object_list(struct FrameObjectList *);
void display_reset_tile_allocation(void), frame_clear_transient_effects(void);
void frame_clear_render_effects(void), frame_release_scene_transient_tiles(void);
void frame_configure_deferred_display(unsigned char), display_reset(void);
void set_vblank_callback(IrqCallback), irq_default_vblank_callback(void);
/* Explicit original providers; signatures are bounded by these calls. */
void scene_stage_0803c598(void), scene_stage_080266b0(void), scene_stage_08026854(void);
unsigned char scene_stage_080269f0(void);
void scene_stage_0800e3a8(unsigned char), scene_update_view(unsigned int);
void scene_stage_080202e0(unsigned char *, unsigned int);
void scene_stage_08026928(void), scene_stage_0802697c(void), scene_stage_0801eea8(void);
void scene_stage_08041374(void), scene_stage_0802eb9c(void);
void scene_stage_0803b8c0(void *), scene_stage_080117bc(void);
#endif
