#ifndef SCENE_RECORD_SELECTION_SETUP_H
#define SCENE_RECORD_SELECTION_SETUP_H

#include "scene_record_selection.h"
#include "display_scene_setup.h"
#include "scene_display.h"
#include "heap.h"
#include "scene_link_catalog_world.h"

extern const unsigned int g_scene_record_selection_control3;
extern const unsigned int g_scene_record_selection_control2;
extern const unsigned int g_scene_record_selection_control1;
extern const unsigned int g_scene_record_selection_titles[];
extern const struct BackgroundResource g_scene_record_selection_background3;
extern const struct BackgroundResource g_scene_record_selection_background2a;
extern const struct BackgroundResource g_scene_record_selection_background2b;
extern const struct BackgroundResource g_scene_record_selection_background1;
extern const struct BackgroundResource g_scene_record_selection_palette;
extern const unsigned short g_scene_record_selection_palette1[];

void display_configure_tile_allocation(unsigned char);
void transition_run_first(unsigned short, unsigned int);
void scene_record_selection_initialize(void);

#endif
