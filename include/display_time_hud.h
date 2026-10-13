#ifndef DISPLAY_TIME_HUD_H
#define DISPLAY_TIME_HUD_H
#include "display_time_format.h"
#include "display_text_raster.h"

/* Partial scene/state access views. Array bounds and surrounding storage remain
 * unestablished; the observed ROM strides are 28 and 8 bytes respectively. */
struct DisplayCountdownSceneState {
    unsigned char unknown_00[18], scene, unknown_13[2], flags;
};
struct DisplayCountdownSceneDefinition {
    unsigned char unknown_00[25], flags, unknown_1a[2];
};
struct DisplayCountdownSceneLayout {
    unsigned short x, y;
    unsigned char left, top, width, height;
};
extern struct DisplayTimeRecord g_display_countdown;
extern const struct DisplayTimeRecord g_display_countdown_tick_delta;
extern const struct DisplayTimeRecord g_display_countdown_second_delta;
extern unsigned int g_frame_flags;
extern struct DisplayCountdownSceneState *g_display_countdown_scene;
extern const struct DisplayCountdownSceneDefinition g_display_countdown_scenes[];
extern const struct DisplayCountdownSceneLayout g_display_countdown_layouts[];
void display_fill_background_constant_rectangle(unsigned int, int, int, int, int,
                                                unsigned short);
void display_clear_background_rectangle(unsigned int, int, int, int, int);
void display_time_step_countdown(void);
void display_time_update_scene_countdown(void);
#endif
