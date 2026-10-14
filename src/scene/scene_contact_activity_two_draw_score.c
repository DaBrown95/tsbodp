#include "scene_contact_activity_two.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_draw_score(void)
{
    char number[16];
    display_clear_background_rectangle(0, 4, 3, 3, 2);
    display_text_select_font(3, 0, 0);
    display_text_draw_line(37, 32, 28,
        display_text_format_number(STATE->score, number), 0);
}
asm(".align 2, 0");
