#ifndef DISPLAY_SCENE_CATALOG_RENDER_H
#define DISPLAY_SCENE_CATALOG_RENDER_H
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"
extern const unsigned int g_display_scene_item_mask[];
extern unsigned char display_scene_item_enabled(const unsigned int *, unsigned int);
extern void display_scene_clear_detail_background(void);
extern void display_scene_redraw_details(unsigned char);
#endif
