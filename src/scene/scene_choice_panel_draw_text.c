#include "scene_choice_panel.h"
#include "display_text_fields.h"

void scene_choice_panel_draw_text(void)
{
    unsigned int tile = 76, palette, width, limit;
    int x;
    int y;
    const char *text;
    unsigned char first;

    x = (g_actor_scene_request.x << 3) + 8;
    y = (g_actor_scene_request.y << 3) + 8;
    width = 200;
    limit = 0x7fffffff;
    if (g_actor_scene_request.active == 1 && g_actor_scene_request.object) {
        x += 32;
        width = 168;
    }
    {
        register unsigned int index asm("r4") = 0;

        while (index < g_actor_scene_request.count) {
            palette = 0;
            if (!g_actor_scene_request.active && g_scene_request.scene == index)
                palette = 3;
            display_text_select_font(3, palette, -1);
            text = display_text_expand_resource(g_need_effect_choice_text[index]);
            first = *text;
            ++index;
            if (first) {
                do {
                    tile = display_text_draw(tile, x, y, width, &text, 0, &limit);
                    y += 12;
                } while (*text);
            }
        }
    }
}

asm(".align 2, 0");
