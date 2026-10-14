#ifndef SCENE_AUDIO_OPTIONS_H
#define SCENE_AUDIO_OPTIONS_H
#include "scene_request.h"
#include "input.h"
#include "audio_game.h"
#include "display_palette_lifecycle.h"
#include "display_text_draw.h"
#include "display_text_fields.h"
#include "display_map_fill.h"
struct FrameObject; struct FrameObjectList; struct BackgroundResource; struct PaletteRangeConfig;
/* Separate observed RAM access views; complete storage ownership is unknown. */
extern unsigned char g_scene_audio_option_levels[2];
extern unsigned int g_scene_audio_option_cue;
extern unsigned char g_scene_audio_option_sequence;
extern unsigned short g_scene_audio_option_return_kind;
extern struct SceneRequest g_scene_previous_request;
extern const unsigned char g_scene_audio_option_limits[2];
extern struct FrameObject *g_display_scene_frame_objects[];
extern struct FrameObjectList g_frame_primary_list;
extern const unsigned int g_scene_audio_option_control0,g_scene_audio_option_control1,g_scene_audio_option_control2;
extern const struct BackgroundResource g_scene_audio_option_background1,g_scene_audio_option_background2,g_display_menu_palette_resource;
extern const struct BackgroundResource *const g_scene_audio_option_text_backgrounds[];
extern const struct PaletteRangeConfig g_display_menu_palette_ranges;
/* Observed row-six scene callbacks and their connected input/render path. */
void scene_audio_options_initialize(void),scene_audio_options_step(void);
void scene_audio_options_shutdown(void);
void scene_audio_options_draw_row(unsigned int);
void scene_audio_options_change_level(void);
void scene_audio_options_choose(void);
void scene_audio_options_change_row(void);
void scene_submit_default_request(unsigned int);
void resource_submit_scene(unsigned int,unsigned int,unsigned int);
unsigned int input_step_local_vertical_pressed(unsigned int *,unsigned int,unsigned int,unsigned char,unsigned char);
unsigned int input_step_local_horizontal_pressed(unsigned int *,unsigned int,unsigned int,unsigned char,unsigned char);
void frame_set_position(struct FrameObject *,int,int);
void transition_run_first(unsigned short,unsigned int);
void transition_run_second(unsigned short,unsigned int);
void display_release_object_list(struct FrameObjectList *);
void display_reset(void);
void display_scene_clear_object_slots(void);
void audio_game_clear_indexed_channels(void);
void audio_game_clear_indexed_channels_alternate(void);
void audio_clear_indexed_channels(void);
int display_bios_div(int,int);
void display_set_mode(unsigned short);
void display_enable_layers(unsigned short);
void display_show_background(unsigned int,unsigned int);
void display_fill_background(unsigned int,unsigned short);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
const unsigned short *display_load_background_dma(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
unsigned int display_load_resource_palette(const struct BackgroundResource *,unsigned short);
void display_load_palette_ranges(const struct PaletteRangeConfig *);
unsigned int display_text_selected_bank(void);
void display_text_set_background_control(unsigned int);
void display_text_select_font(unsigned int,int,int);
struct FrameObject *frame_create_scene_object(unsigned int,unsigned int,unsigned int,unsigned int);
#endif
