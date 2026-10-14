#ifndef SCENE_LINK_MENU_H
#define SCENE_LINK_MENU_H

#include "scene_request.h"
#include "display_text_draw.h"

struct FrameObject;
struct FrameObjectList;
struct BackgroundResource;
extern unsigned int g_frame_flags, g_frame_world_id;
extern volatile unsigned int g_link_flags;
extern struct FrameObjectList g_frame_primary_list;
extern struct FrameObject *g_display_scene_frame_objects[];
extern const unsigned int g_scene_link_menu_background0_control;
extern const unsigned int g_scene_link_menu_background1_control;
extern const unsigned int g_scene_link_menu_background2_control;
extern const struct BackgroundResource g_scene_link_menu_background0;
extern const struct BackgroundResource g_scene_link_menu_background1;
extern const struct BackgroundResource g_display_menu_palette_resource;

void scene_link_menu_initialize(void), scene_link_menu_step(void);
void scene_link_menu_shutdown(void), scene_link_menu_draw_status(void);
/* Connected menu actions; full-word row and selection arguments are observed. */
void scene_link_menu_draw_row(unsigned int, unsigned int);
void scene_link_menu_accept(void), scene_link_menu_change_row(void);
void scene_link_menu_cancel(void);

void display_set_mode(unsigned short), display_enable_layers(unsigned short);
void display_show_background(unsigned int, unsigned int);
void display_fill_background(unsigned int, unsigned short);
const unsigned short *display_load_background(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);
unsigned int display_load_resource_palette(const struct BackgroundResource *,
    unsigned short);
void display_set_background_velocity(unsigned int, int, int);
void display_fill_background_constant_rectangle(unsigned int, int, int, int,
    int, unsigned int);
void display_text_set_background_control(unsigned int);
void display_text_select_font(unsigned int, int, int);
const char *display_scene_lookup_text(unsigned int);
struct FrameObject *frame_create_scene_object(unsigned int, unsigned int,
    unsigned int, unsigned int);
void display_release_object_list(struct FrameObjectList *), display_reset(void);
void display_reset_palette_jobs(void), display_scene_clear_object_slots(void);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);
int transition_link_update(void);
void resource_submit_scene(unsigned int, unsigned int, unsigned int);
unsigned int scene_queued_request_kind(void);
void audio_game_clear_indexed_channels_alternate(void);
void scene_clear_retained_display(void);

#endif
