#include "scene_palette_menu_entry.h"
#include "display_text_draw.h"
#include "scene_palette_menu_selector.h"

void scene_palette_menu_refresh_selector(unsigned int scene)
{
    unsigned int enabled = g_frame_actor_palette_menu_enabled[scene];
    unsigned int color = 1;
    if (enabled) color = 0;
    display_text_select_font(3, color, 0);
    if (scene - 8 <= 4) {
        unsigned int offset = scene - 8;
        unsigned int tile = (unsigned short)(offset * 40 + 1);
        const char *text = display_scene_lookup_text(scene + 460);
        int y = offset * 20 + 43;
        tile = (unsigned short)display_text_draw_line(tile, 24, y, text, 0);
        text = display_scene_lookup_text(scene + 455);
        display_text_draw_line(tile, 172, y, text, 0);
    } else if (scene == 13) {
        const char *text;
        display_fill_background_constant_rectangle(0, 3, 17, 17, 3, 0);
        text = display_scene_lookup_text(*(const unsigned char *)g_scene_palette_menu_owner->parameters + 451);
        display_text_draw_line(201, 79, 143, text, 1);
    } else if (scene == 14) {
        if (!g_scene_palette_menu_owner->initial_word) {
            const char *text = display_scene_lookup_text(31);
            display_text_draw_line(241, 205, 143, text, 1);
        }
    }
}
asm(".align 2,0");
