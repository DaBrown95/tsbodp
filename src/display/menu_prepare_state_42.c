#include "display_menu_pages.h"
#include "audio_game.h"

void display_menu_prepare_state_42(void)
{
    ((struct DisplayMenuActorSelection *)&g_display_catalog_state)->actor = 42;
    display_menu_apply_delta(-10);
    display_load_background_dma(2,
        g_frame_actor_greetings[g_display_menu_state.definition].secondary_background_resource,
        1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
    g_display_menu_state.resource_shown ^= 1;
    audio_play_animation_cue(g_frame_actor_greetings[g_display_menu_state.definition].cue_record[0]);
    display_menu_draw_scrolling_text(0);
}
asm(".align 2, 0");
