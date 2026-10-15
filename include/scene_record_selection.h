#ifndef SCENE_RECORD_SELECTION_H
#define SCENE_RECORD_SELECTION_H

#include "frame.h"
#include "frame_actor_scene.h"
#include "scene_request.h"
#include "frame_actor_need_input.h"
#include "input.h"
#include "save_stream.h"
#include "display_catalog_text.h"
#include "display_text_raster.h"
#include "audio_game.h"

/* The original phase-seven initializer allocates sixteen zeroed bytes.
 * These roles apply to that allocation; names remain provisional. */
struct SceneRecordSelectionState {
 unsigned int return_phase;
 unsigned char occupied[4], enabled[4], unknown_0c[4];
};
extern const unsigned char *g_frame_actor_palette_scene_resource;
#define SCENE_RECORD_SELECTION_STATE \
 ((struct SceneRecordSelectionState *)(void *)g_frame_actor_palette_scene_resource)

extern struct FrameObject *g_condition_panel_objects[15];
extern unsigned int g_scene_link_menu_selector_word;
extern const unsigned int g_scene_record_selection_control0;
struct PaletteRangeConfig;
extern const struct PaletteRangeConfig g_scene_default_menu_palette_ranges;

void scene_record_selection_step(void);
void scene_record_selection_confirm(void);
void scene_record_selection_change_slot(void);
void scene_record_selection_cancel(void);
void scene_record_selection_create_objects(void);
void scene_record_selection_draw_choice(unsigned int, unsigned int);

/* Explicit original-ROM dependencies; these declarations earn no C credit. */
void scene_record_selection_set_phase_original(unsigned char, unsigned int);
void scene_record_selection_set_slot_phase_original(unsigned char, unsigned int);
void scene_record_selection_draw_panel_original(void);

void display_fill_background(unsigned int, unsigned short);
void display_load_palette_ranges(const struct PaletteRangeConfig *);
void display_reset_palette_jobs(void);
void display_scene_retire_object_slot(unsigned int);
void frame_create_palette_scene_actor(unsigned int);
void scene_submit_default_request(unsigned int);
InputU32 input_step_horizontal_pressed(InputU32 *, InputU32, InputU32,
                                      InputU8, InputU8);
unsigned int input_step_local_vertical_pressed(unsigned int *, unsigned int,
    unsigned int, unsigned char, unsigned char);

#endif
