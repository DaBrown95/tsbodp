#include "display_time_hud.h"

void display_time_update_scene_countdown(void)
{
    char text[20];
    const struct DisplayCountdownSceneDefinition *scenes =
        g_display_countdown_scenes;
    unsigned int scene = g_display_countdown_scene->scene;
    if (scenes[scene].flags & 1) {
        if (g_display_countdown_scene->flags & 4) {
            const struct DisplayCountdownSceneLayout *layout =
                &g_display_countdown_layouts[scene];
            int palette;
            display_clear_background_rectangle(0, layout->left, layout->top,
                                                layout->width, layout->height);
            if (g_display_countdown.hour <= 0 && g_display_countdown.minute <= 10)
                palette = 6;
            else
                palette = 0;
            display_text_select_font(3, palette, 0);
            display_time_format(&g_display_countdown, text, 6227);
            display_text_draw_line(1,
                g_display_countdown_layouts[g_display_countdown_scene->scene].x,
                g_display_countdown_layouts[g_display_countdown_scene->scene].y,
                text, 1);
            g_display_countdown_scene->flags &= ~4;
        }
        if (display_time_add(&g_display_countdown, &g_display_countdown_second_delta))
            g_display_countdown_scene->flags |= 4;
    }
}
asm(".align 2, 0");
