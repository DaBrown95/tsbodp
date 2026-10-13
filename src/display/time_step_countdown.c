#include "display_time_hud.h"

void display_time_step_countdown(void)
{
    struct DisplayTimeRecord *time = &g_display_countdown;
    char text[20];
    int palette;
    display_time_add(time, &g_display_countdown_tick_delta);
    if (time->minute <= 0 && time->second <= 5)
        palette = 6;
    else
        palette = 0;
    display_text_select_font(3, palette, 0);
    display_time_format(&g_display_countdown, text, 6226);
    if (!(g_frame_flags & 32))
        display_text_draw_line(25, 46, 36, text, 1);
    else
        display_text_draw_line(25, 46, 74, text, 1);
}
asm(".align 2, 0");
