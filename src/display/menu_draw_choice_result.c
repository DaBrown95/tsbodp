#include "display_menu_results.h"
#include "display_text_fields.h"

void display_menu_draw_choice_result(void)
{
    const struct DisplayMenuTextRecord *const *groups = g_display_menu_text_records;
    struct DisplayMenuState *menu = &g_display_menu_state;
    const struct DisplayMenuChoiceResultRecord *records =
        (const struct DisplayMenuChoiceResultRecord *)groups[menu->record_group];
    unsigned int flags = records[menu->choice].flags;
    if (flags & 0x54) {
        const struct DisplayMenuResultDescriptor *definitions = g_display_menu_result_descriptors;
        display_load_background_dma(2, display_menu_result_resource_column(definitions, menu->record_group, 28),
            1 + 182 * (menu->resource_shown & 1), 0, 15, 0);
        audio_play_animation_cue(display_menu_result_cues(definitions, menu->definition)[6]);
    } else if (flags & 0xa8) {
        const struct DisplayMenuResultDescriptor *definitions = g_display_menu_result_descriptors;
        display_load_background_dma(2, display_menu_result_resource_column(definitions, menu->definition, 4),
            1 + 182 * (menu->resource_shown & 1), 0, 15, 0);
        audio_play_animation_cue(display_menu_result_cues(definitions, menu->definition)[0]);
    } else {
        const struct DisplayMenuResultDescriptor *definitions = g_display_menu_result_descriptors;
        display_load_background_dma(2, display_menu_result_resource_column(definitions, menu->definition, 12),
            1 + 182 * (menu->resource_shown & 1), 0, 15, 0);
        audio_play_animation_cue(display_menu_result_cues(definitions, menu->definition)[2]);
    }
    g_display_menu_state.resource_shown ^= 1;
    display_text_copy_field_zero((const char *)&g_display_menu_relation_state);
    display_menu_draw_scrolling_text(display_scene_lookup_text(records[g_display_menu_state.choice].text));
}

asm(".align 2, 0");
