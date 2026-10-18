#include "display_menu_pages.h"
#include "display_catalog_presentation.h"

void display_menu_draw_scrolling_text(const char *text)
{
    unsigned int remaining = 0x7fffffff;
    unsigned int tile;
    int y;
    if (((struct FrameActorRelationState *)&g_display_catalog_state)
            ->records[g_display_menu_state.definition].unknown_02[0])
        text = display_scene_lookup_text(
            g_frame_actor_greetings[g_display_menu_state.definition].text_ids[5]
            + g_display_menu_page_text_variants[0]);
    display_text_select_font(3, 0, -1);
    display_text_set_line_height(12);
    g_display_scene_request_state.scene = 0;
    g_display_scene_request_state.parameter = 0;
    tile = 258;
    y = 32;
    do {
        tile = display_text_draw(tile, 16, y, 104, &text, 0, &remaining);
        y += 12;
        ++g_display_scene_request_state.parameter;
    } while (*text);
    g_display_scene_request_state.parameter =
        (unsigned int)(g_display_scene_request_state.parameter - 5.0);
    g_display_scene_request_state.parameter =
        (int)g_display_scene_request_state.parameter >= 0
        ? g_display_scene_request_state.parameter + 1 : 0;
    if (g_display_scene_request_state.scene == g_display_scene_request_state.parameter
        || g_display_scene_request_state.parameter == 0) {
        g_display_menu_objects.scroll->flags &= ~1;
        g_display_menu_objects.hint->flags |= 1;
    } else {
        g_display_menu_objects.scroll->flags |= 1;
        g_display_menu_objects.hint->flags &= ~1;
    }
}
/* Compiler-generated arithmetic calls: __floatsidf __adddf3 __subdf3 __fixunsdfsi. */
asm(".align 2, 0");
