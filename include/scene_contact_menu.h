#ifndef SCENE_CONTACT_MENU_H
#define SCENE_CONTACT_MENU_H
#include "display_time_hud.h"
#include "display.h"
#include "display_text_fields.h"
#include "scene_request.h"
#include "heap.h"
#include "frame.h"
#include "transition_object.h"
#include "frame_contact_action.h"
#include "audio_game.h"
#include "resource_decode.h"
#include "scene_contact_activity.h"

/* Kind-20 scene access views. These are observed prefixes, not recovered
 * original declarations. The original initializer allocates 420 bytes. */
struct SceneContactState {
    unsigned char unknown00[8];
    short amount;
    unsigned char unknown0a[6];
    unsigned char return_mode, result, scene, option, phase, flags;
};
struct SceneContactCursor {
    unsigned char unknown00[0x4e], state;
};
struct SceneContactRequirement {
    unsigned char first_parameter, first_thresholds[4];
    unsigned char second_parameter, second_thresholds[4];
};
union SceneContactResource {
    struct {
        const struct BackgroundResource *background, *next_background;
        const struct SceneContactRequirement *requirements;
        unsigned short costs[4], labels[6];
    } fields;
    unsigned int words[8];
    unsigned short halfwords[16];
};
struct SceneContactDefinition {
    SceneContactActivityCallback initialize, step;
    struct DisplayTimeRecord elapsed;
    unsigned char need_deltas[8], sequence, flags;
    unsigned short unknown1a;
};
/* This view is rooted at game+0x98. Its values at +0x69D are the same bytes
 * as ContactWorldView.values at game+0x735. Complete storage is unknown. */
struct SceneContactParameterStorage {
    unsigned char unknown00[0x69d], values[8];
};
typedef unsigned int (*SceneContactNoticeHandler)(unsigned int,
    unsigned short *, unsigned short *);

extern struct SceneContactState *g_scene_contact_state;
extern const struct DisplayCountdownSceneLayout g_scene_contact_value_layouts[];
extern const unsigned int g_scene_contact_background_control;
extern const unsigned int g_scene_contact_completion_background_control1;
extern const struct BackgroundResource g_scene_contact_palette_resource;
extern const struct PaletteRangeConfig g_scene_contact_palette_ranges;
extern struct SceneRequest g_scene_previous_request;
extern const union SceneContactResource g_scene_contact_resources[];
extern const struct SceneContactDefinition g_scene_contact_definitions[];
extern struct SceneContactParameterStorage g_scene_contact_parameter_storage;
extern unsigned int g_scene_contact_return_argument;

void scene_contact_step(void);
void scene_contact_refresh_value(void);
void scene_contact_prepare_backdrop(void);
void scene_contact_shutdown(void);
unsigned int scene_contact_handle_input_notice(unsigned int, unsigned short *,
                                              unsigned short *);
unsigned int scene_contact_test_progress(void);
void scene_contact_mark_conditions(void);
void scene_contact_clear_activity_objects(void);
void scene_contact_start_activity(void);
void scene_contact_show_completion(void);

/* Explicit original providers. Their declarations describe observed call
 * operands; these bodies are not new C coverage in this batch. */
void scene_contact_initialize(void);
void scene_contact_apply_need_adjustments(void);
unsigned int scene_contact_original_service_mode(void);

int frame_read_signed_parameter(const void *, unsigned int);
int frame_add_game_value(int);
void resource_set_triple(unsigned int, unsigned int, unsigned int);
void display_time_step_world(const struct DisplayTimeRecord *);
void display_show_background(unsigned int, unsigned int);
void display_fill_background(unsigned int, unsigned short);
const unsigned short *display_load_background(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);
void display_set_mode(unsigned short);
void display_configure_tile_allocation(unsigned char);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);
void transition_configure_alpha(unsigned short, unsigned short);
void frame_clear_scene_effects(void);
void display_release_object_list(struct FrameObjectList *);
void audio_game_clear_indexed_channels_alternate(void);
void display_reset_palette_jobs(void);
void display_reset(void);
void frame_release_map_resources(void);
void set_vblank_callback(void (*)(void));
void irq_default_vblank_callback(void);
#endif
