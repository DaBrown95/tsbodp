#ifndef SCENE_ENVIRONMENT_H
#define SCENE_ENVIRONMENT_H

#include "frame_map_scene.h"
#include "background_animation.h"
#include "scene_retention.h"
#include "frame_need_effect_clear.h"

/* A bounded access view of the current clock and two event clocks. This does
 * not establish the complete world-record extent or all clock ownership. */
struct SceneTimeTriggers {
    struct DisplayTimeRecord time;
    unsigned char unknown_08[0x71c - 8];
    struct DisplayTimeRecord first, second;
    unsigned char enabled;
};
/* Twelve-byte table also accessed as ScenePaletteRangeConfig; its last word
 * supplies one audio-sequence byte per observed clock period. */
struct ScenePeriodAudio {
    unsigned char unknown_00[8], sequences[4];
};
extern const struct ScenePeriodAudio g_scene_period_audio[];
void scene_refresh_environment(void), scene_refresh_period_audio(void);
void scene_allocate_retained_palette(void), scene_retain_display(void);
void scene_release_display(void), scene_clear_retained_display(void);
unsigned char scene_step_early_exit(void);
void background_animation_force_reload(void), background_animation_stop_default(void);

/* Connected cleanup interfaces retain their existing shared types. */
void display_release_object_list(struct FrameObjectList *);
extern struct FrameObjectList g_frame_primary_list;
extern void *g_frame_registration;
void frame_clear_transient_effects(void), frame_clear_render_effects(void);
#endif
