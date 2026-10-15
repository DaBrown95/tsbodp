#ifndef SCENE_RELATION_GRID_H
#define SCENE_RELATION_GRID_H
#include "scene_link_catalog.h"
#include "display_menu_relation_events.h"
#include "display_map_fill.h"
/* This observed world prefix reaches the final sixth signed-parameter byte at+9F.
 * Its byte representation supports the actual+18/+20/+88 input addresses;
 * complete storage and original C ownership remain unknown. */
struct SceneRelationGridWorld { unsigned char bytes[160]; };
struct SceneRelationGridTextPoint { short x,y; };
extern struct SceneRelationGridWorld g_scene_relation_grid_world;
extern unsigned int g_scene_relation_grid_indices[24];
extern const unsigned int g_scene_relation_grid_control3,g_scene_relation_grid_control2,g_scene_relation_grid_control1,g_scene_relation_grid_control0;
extern const struct BackgroundResource g_scene_relation_grid_background3,g_scene_relation_grid_background2;
extern const unsigned short g_scene_relation_grid_icon_palette[];
extern struct FrameVariantResource g_scene_relation_grid_indicator_animation;
/* Four explicit original service boundaries, not recovered C definitions. */
unsigned int scene_relation_grid_trait_original(const void *,unsigned int);
unsigned int scene_relation_grid_descriptor_original(const void *);
void scene_relation_grid_relation_original(struct FrameObject *,unsigned int,struct SceneRelationGridTextPoint,unsigned int);
void scene_relation_grid_initialize(void),scene_relation_grid_step(void),scene_relation_grid_shutdown(void);
void scene_relation_grid_create_objects(void),scene_relation_grid_draw_detail(void);
/* Refresh remains original at 0x08036744; its two-byte candidate is unaccepted. */
void scene_relation_grid_refresh_entries_original(void);
void scene_relation_grid_sort_relations(const struct DisplayMenuRelationValues *);
struct FrameObject *scene_relation_grid_create_indicator(unsigned int,unsigned int,unsigned int);
void frame_set_animation_frame(struct FrameTickObject *object, FrameU8 frame);
struct FrameObject *frame_allocate_object(int id);
void display_release_object_list(struct FrameObjectList *list);
void frame_set_animation_record(struct FrameObject *base, struct FrameVariantResource *resource);
void frame_set_position(struct FrameObject *object, int x, int y);
void frame_set_variant_state(struct FrameObject *base, FrameU8 variant);
void display_show_background(unsigned int index, unsigned int control);
void display_set_mode(unsigned short mode);
void display_enable_layers(unsigned short mask);
void display_fill_background(unsigned int index, unsigned short tile);
void display_clear_background_rectangle(unsigned int index, int x, int y, int width, int height);
void display_fill_background_constant_rectangle(unsigned int index, int x, int y, int width, int height, unsigned int tile);
const unsigned short *display_load_background(unsigned int index, const struct BackgroundResource *resource, unsigned short tile, unsigned short palette, unsigned int x, unsigned int y);
unsigned int display_load_resource_palette(const struct BackgroundResource *resource, unsigned short extra_bank);
void display_reset(void);
void display_set_background_velocity(unsigned int index, int x, int y);
void display_load_palette_alternate(const void *source, unsigned int first, unsigned int count);
void display_reset_palette_jobs(void);
unsigned int display_text_draw(unsigned int tile, int x, int y, int max_width, const char **text, unsigned int style, unsigned int *limit);
unsigned int display_text_draw_line(unsigned int tile, int input_x, int input_y, const char *input, unsigned int style);
void display_text_set_background_control(unsigned int control);
void display_text_select_font(unsigned int group, int palette, int fill);
void display_text_copy_field_zero(const char *source);
void display_text_number_field_zero(int value);
void scene_submit_default_request(unsigned int kind);
void resource_submit_scene(unsigned int kind,unsigned int mode,unsigned int argument);
struct FrameObject *frame_create_scene_object(unsigned int id,unsigned int subtype,unsigned int palette,unsigned int layer);
void display_scene_refresh_item(struct FrameObject *object);
void display_scene_clear_object_slots(void);
unsigned char display_menu_relation_initialized(void *pointer, unsigned int index);
int display_menu_read_relation_average(struct DisplayMenuRelationState *state);
void transition_run_first(unsigned short targets, unsigned int kind);
void transition_run_second(unsigned short targets, unsigned int kind);
int frame_read_signed_parameter(const void *state,unsigned int index);
unsigned int audio_play_animation_cue(unsigned int id);
const char *display_scene_lookup_text(unsigned int id);
typedef char grid_pointer_word[(sizeof(void*)==4&&sizeof(unsigned int)==4)?1:-1];
typedef char grid_world_prefix[(sizeof(struct SceneRelationGridWorld)==160&&__alignof__(struct SceneRelationGridWorld)==4)?1:-1];
typedef char grid_text_point[(sizeof(struct SceneRelationGridTextPoint)==4&&__alignof__(struct SceneRelationGridTextPoint)==4&&(unsigned int)&((struct SceneRelationGridTextPoint*)0)->y==2)?1:-1];
typedef char grid_indices[(sizeof(g_scene_relation_grid_indices)==96)?1:-1];
typedef char grid_frame_view[(sizeof(struct FrameObject)==312&&__alignof__(struct FrameObject)==4)?1:-1];
typedef char grid_resource[(sizeof(struct FrameVariantResource)==16)?1:-1];
typedef char grid_input[(sizeof(struct InputConfig)==52&&(unsigned int)&((struct InputConfig*)0)->local_player==49)?1:-1];
#endif
