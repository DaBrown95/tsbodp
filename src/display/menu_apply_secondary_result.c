#include "display_menu_results.h"

void display_menu_apply_secondary_result(void)
{
    const struct DisplayMenuResult *result;
    const struct DisplayMenuSecondaryResultRow *row;
    if (g_display_menu_state.codes[g_display_scene_request_state.scene] == 14) {
        struct DisplayMenuResultObserver *game = &g_display_menu_result_observer;
        if (game->variant != g_frame_actor_greetings[g_display_menu_state.definition].cue_variant)
            display_menu_try_relation_flag((unsigned char *)game + 0x30,
                                           g_display_menu_state.definition);
    }
    row = &g_display_menu_secondary_result_rows[g_display_menu_state.definition];
    result = (const struct DisplayMenuResult *)((unsigned int)row + g_display_menu_state.codes[g_display_scene_request_state.scene] * sizeof(*result));
    display_menu_apply_delta(result->delta);
    display_menu_draw_secondary_result(result->text);
}

asm(".align 2, 0");
