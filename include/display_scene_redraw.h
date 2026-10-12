#ifndef DISPLAY_SCENE_REDRAW_H
#define DISPLAY_SCENE_REDRAW_H
#include "display_text_raster.h"
#include "display_text_fields.h"
#include "display_scene_setup.h"
#include "input.h"
extern struct DisplaySceneOwner *g_display_scene_objects[];
struct DisplaySceneTextState {
    unsigned int unknown_00, text_id;
    unsigned char unknown_08[8];
    char buffer[1];
};
extern struct DisplaySceneTextState g_display_scene_text_state;
extern const unsigned int g_display_scene_group_text_ids[6];
struct FrameObject;
extern struct FrameObject *frame_create_scene_object(unsigned int, unsigned int, unsigned int, unsigned int);
extern const char *display_scene_lookup_text(unsigned int);
extern struct DisplaySceneOwner *display_scene_stage_080282d4(unsigned int, const char **);
struct TransitionObject;
extern void transition_object_set_state(struct TransitionObject *, unsigned char);
extern unsigned char display_scene_item_enabled(const unsigned int *, unsigned int);
extern void display_scene_create_objects(void), display_scene_redraw_group_labels(unsigned char);
#endif
