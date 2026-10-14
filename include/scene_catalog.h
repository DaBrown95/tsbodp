#ifndef SCENE_CATALOG_H
#define SCENE_CATALOG_H
#include "display_scene_setup.h"
#include "display_time.h"
#include "scene_request.h"
struct FrameObjectList;
/* Partial views; array lengths and object validity are not runtime guarantees. */
struct SceneCatalogState {unsigned char page_start,count,row,value,selector;};
struct __attribute__((packed,aligned(1))) SceneCatalogCount {unsigned char count;};
struct SceneCatalogEntry {unsigned char value,unknown01[7];};
struct SceneCatalogWorld {
 unsigned char unknown00[8];struct DisplayTimeRecord clock;
 unsigned char unknown10[0xe0-0x10];unsigned char quantities[9],values[7];struct SceneCatalogCount *catalog;
 unsigned char unknownf4[4];/* Observed selector prefix 0..13; complete capacity is unknown. */
 struct SceneCatalogEntry entries[14];
};
struct SceneCatalogHour {unsigned char unknown00[2];signed char hour;};
extern struct SceneCatalogState g_scene_catalog_state;
extern struct SceneCatalogWorld g_scene_catalog_world;
extern const struct SceneCatalogHour g_scene_catalog_start_hour,g_scene_catalog_end_hour;
extern unsigned char g_scene_catalog_last_row,g_scene_catalog_first_row,g_scene_catalog_action_row;
extern struct SceneRequest g_scene_previous_request;
extern unsigned int g_scene_catalog_bg0,g_scene_catalog_bg0_alt,g_scene_catalog_bg1,g_scene_catalog_bg1_alt,g_scene_catalog_bg2,g_scene_catalog_bg3;
extern const struct BackgroundResource g_scene_catalog_palette,g_scene_catalog_background3,g_scene_catalog_background3_alt,g_scene_catalog_background2,g_scene_catalog_background2_alt,g_scene_catalog_background1;
extern const unsigned short g_scene_catalog_text_palette[];
extern struct FrameObjectList g_scene_catalog_objects;
void display_enable_layers(unsigned short);
unsigned int display_load_resource_palette(const struct BackgroundResource *,unsigned short);
void display_load_palette(const void *,unsigned int,unsigned int);
const char *display_scene_lookup_text(unsigned int);
void transition_run_first(unsigned short,unsigned int);
void transition_run_second(unsigned short,unsigned int);
void display_release_object_list(struct FrameObjectList *);
void display_reset(void),display_reset_palette_jobs(void),display_scene_clear_object_slots(void);
/* Original object preparation remains explicit; connected display providers match C. */
void scene_catalog_prepare_original(void),scene_catalog_update(void),scene_catalog_build(void);
void scene_catalog_draw(unsigned int,unsigned int),scene_catalog_fill(unsigned int,unsigned int);
extern struct FrameObject *g_display_scene_frame_objects[];
extern unsigned int g_frame_world_id;
int frame_add_game_value(int);
void resource_set_triple(unsigned int,unsigned int,unsigned int);
void resource_submit_scene(unsigned int,unsigned int,unsigned int);
unsigned int audio_play_animation_cue(unsigned int);
void display_hide_background(unsigned int);
void scene_catalog_previous(void),scene_catalog_next(void),scene_catalog_selection(void);
void scene_catalog_confirm_original(void),scene_catalog_option(void),scene_catalog_begin_quantity(void);
void scene_catalog_quantity(void),scene_catalog_refresh_quantities(void);
void display_scene_refresh_item(struct FrameObject *);
void frame_set_variant_state(struct FrameObject *,unsigned char);
void scene_catalog_initialize(void), scene_catalog_step(void), scene_catalog_shutdown(void);
#endif
