#ifndef SCENE_TEXT_BANK_H
#define SCENE_TEXT_BANK_H
#include "display_text_slots.h"
struct FrameObjectList;
#include "input.h"
#include "scene_request.h"
#include "save_stream.h"
#include "display_text_raster.h"
struct BackgroundResource;
extern struct SceneRequest g_scene_previous_request;
/* Read-only control, palette and background access views; bounds are unknown. */
extern const unsigned int g_scene_text_bank_control;
extern const struct BackgroundResource g_scene_text_bank_palette_resource;
extern const unsigned short g_scene_text_bank_palette[];
extern const struct BackgroundResource *const g_scene_text_bank_backgrounds[];
void scene_text_bank_initialize(void),scene_text_bank_step(void),scene_text_bank_shutdown(void);
void scene_text_bank_load_preview(unsigned int),scene_text_bank_apply_selection(void),scene_text_bank_return_previous(void),scene_text_bank_change_selection(void);
void scene_text_bank_create_row(unsigned int),scene_text_bank_redraw_row(unsigned int);
void frame_set_centered_integer_position(struct FrameObject *,short,int);
void display_set_mode(unsigned short),display_configure_tile_allocation(unsigned char),display_enable_layers(unsigned short),display_show_background(unsigned int,unsigned int);
void display_fill_background_map(unsigned int,unsigned short,unsigned short);
void display_fill_background_rectangle(unsigned int,int,int,int,int,unsigned short);
void display_set_background_velocity(unsigned int,int,int);
unsigned int display_load_resource_palette(const struct BackgroundResource *,unsigned short);
void display_load_palette_alternate(const unsigned short *,unsigned short,unsigned short);
const unsigned short *display_load_background_dma(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
void display_release_object_list(struct FrameObjectList *),display_reset(void);
void transition_run_first(unsigned short,unsigned int),transition_run_second(unsigned short,unsigned int);
void scene_submit_default_request(unsigned int),resource_submit_scene(unsigned int,unsigned int,unsigned int);
/* Explicit original header-commit provider; its comparison loop is unresolved. */
unsigned int save_stream_commit_header(void);
unsigned int audio_play_animation_cue(unsigned int);
unsigned int input_step_local_vertical_pressed(unsigned int *,unsigned int,unsigned int,unsigned char,unsigned char);
const char *display_scene_lookup_text(unsigned int);
extern struct FrameObjectList g_frame_primary_list;
#endif
