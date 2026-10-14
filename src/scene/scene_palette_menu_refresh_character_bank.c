#include "scene_palette_menu_input.h"
void scene_palette_menu_refresh_character_bank(void)
{
    const struct DisplayTextTemplateEntry *entries;
    struct FrameObject *object;
    display_fill_background(0, 0);
    display_text_set_background_control(g_scene_palette_menu_control0);
    display_text_select_font(1, 0, -1);
    {
        unsigned int flag = g_frame_actor_palette_menu_text_flag;
        entries = g_palette_menu_entry_template;
        if (flag)
            entries = g_palette_menu_upper_template;
    }
    display_text_draw_template(1, 37, entries);
    object = g_frame_actor_palette_menu_objects[12];
    if (object->id == 134)
        object->id = 130;
    else
        object->id = 134;
    frame_set_variant_state(g_frame_actor_palette_menu_objects[12], 58);
}
asm(".align 2,0");
