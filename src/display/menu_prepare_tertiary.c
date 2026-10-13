#include "display_menu_pages.h"

void display_menu_prepare_tertiary(void)
{
    g_display_scene_request_state.unknown_10 = 1;
    display_menu_show_hint(1);
    display_load_background_dma(2,
        g_frame_actor_greetings[g_display_menu_state.definition].secondary_background_resource,
        1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
    g_display_menu_state.resource_shown ^= 1;
    if (g_display_menu_state.definition == 0) {
        transition_object_set_state((struct TransitionObject *)g_need_effect_player, 0);
        transition_object_set_state(
            (struct TransitionObject *)g_need_effect_player->unknown_90, 45);
        frame_set_variant_state(
            (struct FrameObject *)g_need_effect_player->unknown_90, 4);
    }
    display_menu_draw_scrolling_text(0);
}
asm(".align 2, 0");
