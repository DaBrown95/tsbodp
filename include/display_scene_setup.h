#ifndef DISPLAY_SCENE_SETUP_H
#define DISPLAY_SCENE_SETUP_H
#include "display_motion.h"
struct DisplaySceneRequestState {
    unsigned int unknown_00, mode, scene, parameter, unknown_10, unknown_14;
};
struct DisplaySceneOwner { unsigned int unknown_00[2]; unsigned short id, unknown_0a; unsigned int flags; };
struct DisplaySceneOwnerLink { struct DisplaySceneOwner *first_owner, *owner; };
extern struct DisplaySceneRequestState g_display_scene_request_state;
extern struct DisplaySceneOwnerLink g_display_scene_owner_link;
extern const unsigned int g_display_scrolling_layer_control0, g_display_scrolling_layer_control1, g_display_scrolling_layer_control2;
extern const struct BackgroundResource g_display_scrolling_resource3, g_display_scrolling_resource1, g_display_scrolling_palette;
extern unsigned char g_display_scene_byte0, g_display_scene_byte1, g_display_scene_byte2;
extern void display_set_mode(unsigned short), display_show_background(unsigned int, unsigned int);
extern void display_fill_background(unsigned int, unsigned short);
extern const unsigned short *display_load_background(unsigned int, const struct BackgroundResource *, unsigned short, unsigned short, unsigned int, unsigned int);
extern void display_scene_stage_0801ae2c(unsigned int), display_scene_stage_0800f168(void), display_scene_stage_0800f034(unsigned int), display_scene_stage_0800ef2c(unsigned int), display_scene_stage_0800f478(void);
extern void display_initialize_scrolling_scene(void);
#endif
