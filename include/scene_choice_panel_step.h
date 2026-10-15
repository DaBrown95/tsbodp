#ifndef SCENE_CHOICE_PANEL_STEP_H
#define SCENE_CHOICE_PANEL_STEP_H
#include "scene_choice_panel.h"
#include "input.h"
#include "display_map_fill.h"
#include "scene_view_frame.h"

#include "frame_actor_need_input.h"
#include "scene_link_catalog_world.h"

#define SCENE_CHOICE_PANEL_LOCAL_PLAYER (g_frame_actor_need_input.local_player)
#define SCENE_CHOICE_PANEL_INPUT_ACTOR(i) (g_frame_actor_need_input.views[(i)].actor)
#define SCENE_CHOICE_PANEL_ACTOR_STATE(o) (((const unsigned char *)(o))[77])
#define SCENE_CHOICE_PANEL_ACTOR_VARIANT(o) (((const unsigned char *)(o))[78])
#define SCENE_CHOICE_PANEL_REQUESTED_KIND (g_scene_link_catalog_world.requested_kind)

void scene_choice_panel_step(void);
InputU32 input_step_vertical_pressed(InputU32 *,InputU32,InputU32,InputU8,InputU8);
void scene_submit_default_request(unsigned int);
#endif
