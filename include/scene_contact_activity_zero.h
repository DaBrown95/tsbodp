#ifndef SCENE_CONTACT_ACTIVITY_ZERO_H
#define SCENE_CONTACT_ACTIVITY_ZERO_H
#include "frame_actor_items.h"
#include "frame_scene_player.h"
#include "frame_option_object.h"
#include "display_scene_setup.h"
#include "display_transient_definition.h"
#include "heap.h"

extern const unsigned int g_activity_zero_background_control;
extern const struct BackgroundResource g_activity_zero_background;
extern const void *const g_activity_zero_palettes[];
extern const void *const g_activity_zero_palette14[];
extern const void *const g_activity_zero_palette15[];
extern struct FrameSpriteResource g_activity_zero_transient0, g_activity_zero_transient1;
extern const struct FramePoint g_activity_zero_start;
void frame_define_palette_slot(unsigned int, const void *const *);
void scene_contact_activity_zero_initialize(void);
#endif
