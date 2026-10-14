#ifndef SCENE_PALETTE_MENU_H
#define SCENE_PALETTE_MENU_H
#include "frame_actor_palette_menu_transition.h"
#include "heap.h"
#include "display_palette_lifecycle.h"
/* Observed308-byte storage; byte-derived counts remain unchecked. */
struct ScenePaletteMenuOwner {
    unsigned int initial_word;
    struct FrameObject *available[25];
    struct FrameObject *groups[5][10];
    const void *parameters;
};
extern struct ScenePaletteMenuOwner *g_scene_palette_menu_owner;
/* Existing game-state +0x28 storage, viewed only as an address here. */
extern const unsigned char g_scene_palette_menu_parameter_base[];
extern const unsigned int g_scene_palette_menu_control0,g_scene_palette_menu_control1,g_scene_palette_menu_control2,g_scene_palette_menu_control3;
extern const unsigned short g_scene_palette_menu_palette[];
extern const struct BackgroundResource g_scene_palette_menu_background3;
void scene_palette_menu_initialize(void),scene_palette_menu_shutdown(void),scene_palette_menu_step(void);
void scene_palette_menu_phase_0(void),scene_palette_menu_phase_1(void),scene_palette_menu_phase_6(void),scene_palette_menu_phase_8(void),scene_palette_menu_phase_4(void),scene_palette_menu_phase_9(void),scene_palette_menu_phase_10(void),scene_palette_menu_phase_11(void),scene_palette_menu_phase_12(void),scene_palette_menu_phase_5(void);
void display_set_mode(unsigned short),display_enable_layers(unsigned short),display_configure_background(unsigned int,unsigned int),display_show_background(unsigned int,unsigned int),display_fill_background(unsigned int,unsigned short);
const unsigned short *display_load_background(unsigned int,const struct BackgroundResource *,unsigned short,unsigned short,unsigned int,unsigned int);
void display_set_background_velocity(unsigned int,int,int);
void display_release_object_list(struct FrameObjectList *),display_reset(void),display_scene_clear_object_slots(void);
void audio_select_sequence(unsigned char);
void transition_run_first(unsigned short,unsigned int),transition_run_second(unsigned short,unsigned int);
#endif
