#include "display_menu_secondary.h"

struct MenuSecondaryCaptionPoint { signed int x:16; signed int y:16; };
static inline void secondary_relation_caption(int relation, struct MenuSecondaryCaptionPoint position)
{
    const char *caption;
    display_text_select_font(0, 0, -1);
    display_text_number_field_zero(relation);
    caption = display_scene_lookup_text(6222);
    display_text_draw_line(442, position.x, position.y, caption, 2);
    display_text_copy_field_zero((const char *)&g_menu_secondary_relation_owner.state);
}

/* The original signed shifts require valid indices below31. The initialized
 * secondary list has eight slots; other writers and definition bounds remain
 * caller/backing premises, as do the descriptor and selected-entry pointers. */
void display_menu_prepare_secondary(void)
{
    struct ConditionActorEntries *list = g_menu_secondary_world.secondary_entries;
    struct ConditionActorEntry *entry = list->entries;
    unsigned int kind = 255;
    unsigned int selected = g_display_scene_request_state.scene;
    int count = 0;
    int index = 0;
    unsigned int accepted, is_choice, text_id;
    struct MenuSecondaryCaptionPoint position;
    for (; index < list->capacity; ++index) {
        if ((1 << index) & selected) {
            if (kind == 255)
                kind = entry[index].kind;
            ++count;
        }
    }
    accepted = 0;
    is_choice = 0;
    if (kind == 129) {
        if (!(g_menu_secondary_world.once_mask & (1 << g_display_menu_state.definition))) {
            g_menu_secondary_world.once_mask |= (1 << g_display_menu_state.definition);
            accepted = 1;
        }
    } else if (kind - 171 > 23) {
        unsigned int i = 0;
        unsigned int length = g_menu_secondary_descriptors[g_display_menu_state.definition].allowed_count;
        if (i < length) {
            const unsigned int *allowed = g_menu_secondary_descriptors[g_display_menu_state.definition].allowed;
            do {
                if (*allowed == kind)
                    accepted = 1;
                ++allowed;
                ++i;
            } while (i < length);
        }
    } else {
        if (g_menu_secondary_world.selection.text_kind == g_display_menu_state.definition) {
            if (display_menu_test_choice_stamp(&g_menu_secondary_world.selection,
                                               &g_menu_secondary_world.clock))
                accepted = 1;
            else {
                for (index = list->capacity - 1; index >= 0; --index)
                    if ((1 << index) & selected)
                        condition_update_actor(list, index, 1);
            }
            is_choice = 1;
        }
    }
    if (g_display_menu_state.definition == 7 &&
        (unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 4) <= 3)
        text_id = 2241;
    else
        text_id = g_menu_secondary_descriptors[g_display_menu_state.definition].text_ids[5];
    g_display_scene_request_state.unknown_10 = 1;
    if (accepted == 1) {
        for (index = list->capacity - 1; index >= 0; --index)
            if ((1 << index) & selected)
                condition_update_actor(list, index, 1);
        display_menu_resolve_selected_kind(kind, count);
        display_load_background_dma(2,
            g_menu_secondary_descriptors[g_display_menu_state.definition].resources[4],
            1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
        g_display_menu_state.resource_shown ^= 1;
        audio_play_animation_cue(g_menu_secondary_descriptors[g_display_menu_state.definition].cues[4]);
        if (is_choice) {
            display_menu_apply_delta(3);
            display_menu_adjust_relation(&g_menu_secondary_relation_owner.state,
                                        g_menu_secondary_relation_owner.selected_definition, 3);
            display_text_number_field_two(g_menu_secondary_reward_multipliers[g_menu_secondary_descriptors[g_display_menu_state.definition].multiplier] *
                g_menu_secondary_relation_owner.reward);
            frame_add_game_value(g_menu_secondary_reward_multipliers[g_menu_secondary_descriptors[g_display_menu_state.definition].multiplier] *
                g_menu_secondary_relation_owner.reward);
            display_menu_draw_scrolling_text(display_scene_lookup_text(text_id + g_display_menu_page_text_variants[2]));
        } else {
            if (kind != 125 && kind != 142) {
                int relation;
                struct FrameObject *indicator;
                unsigned int definition;
                int percent, frame;
                position.x = 238;
                position.y = 96;
                display_menu_adjust_relation(&g_menu_secondary_relation_owner.state, g_display_menu_state.definition,
                    (unsigned short)frame_random_bounded(4) + 1);
                display_menu_show_change(6);
                display_menu_restore_footer();
                display_text_set_background_control(g_display_menu_control1);
                indicator = g_display_scene_frame_objects[0];
                definition = g_display_menu_state.definition;
                relation = display_menu_read_relation(&g_menu_secondary_relation_owner.state.values, definition);
                if (relation > 0) {
                    percent = save_world_ratio_percent(relation, 100);
                    frame = save_world_scale_percent(10, (unsigned short)percent);
                    frame_set_animation_frame((struct FrameTickObject *)indicator,
                                               (unsigned char)(frame + 10));
                } else {
                    register int numerator asm("r0") = relation;
                    int denominator = -100;
                    percent = save_world_ratio_percent(numerator, denominator);
                    frame = save_world_scale_percent(10, (unsigned short)percent);
                    frame_set_animation_frame((struct FrameTickObject *)indicator,
                                               (unsigned char)(10 - frame));
                }
                secondary_relation_caption(relation, position);
                display_text_set_background_control(g_display_menu_control0);
            }
            display_menu_draw_scrolling_text(display_scene_lookup_text(text_id));
        }
        display_menu_show_hint(1);
    } else {
        display_load_background_dma(2,
            g_menu_secondary_descriptors[g_display_menu_state.definition].resources[5],
            1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
        g_display_menu_state.resource_shown ^= 1;
        audio_play_animation_cue(g_menu_secondary_descriptors[g_display_menu_state.definition].cues[5]);
        if (is_choice) {
            unsigned int actor = g_menu_secondary_relation_owner.selected_definition;
            display_menu_adjust_relation(&g_menu_secondary_relation_owner.state, actor, frame_random_range(-1,-6));
            display_menu_draw_scrolling_text(display_scene_lookup_text(text_id + g_display_menu_page_text_variants[3]));
        } else
            display_menu_draw_scrolling_text(display_scene_lookup_text(text_id + 1));
        display_menu_show_hint(1);
    }
}

asm(".align 2, 0");
