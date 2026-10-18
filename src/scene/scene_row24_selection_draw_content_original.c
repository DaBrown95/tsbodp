#include "scene_row24_selection_private.h"

void scene_row24_selection_draw_content_original(void)
{
    unsigned int tile;
    int y;
    unsigned int level, first_parameter, second_parameter;
    const struct SceneContactRequirement *requirements;
    unsigned int condition_index, condition_row;
    const char *text;

    y = 84;
    tile = 4;
    display_text_set_background_control(g_scene_row24_selection_control0);
    display_text_select_font(3, 0, -1);
    display_fill_background(0, 0);
    condition_row = g_contact_action_conditions[
        condition_index = g_scene_row24_selection_value_permutation[g_scene_request.scene]].row;
    if (!(unsigned char)condition_group_complete(condition_row, g_contact_action_conditions[condition_index].column)) {
        text = display_scene_lookup_text(6231);
        scene_row24_selection_draw_lines(&tile, 85, &y, text);
        return;
    }
    level = g_contact_action_world.values[
        g_scene_row24_selection_value_permutation[g_scene_request.scene]];
    if (level == 4) {
        y = 114;
        text = display_scene_lookup_text(280);
        scene_row24_selection_draw_lines(&tile, 85, &y, text);
        return;
    }
    text = display_scene_lookup_text(272);
    scene_row24_selection_draw_lines(&tile, 85, &y, text);
    requirements = g_scene_contact_resources[
        g_scene_row24_selection_value_permutation[g_scene_request.scene]].fields.requirements;
    first_parameter = requirements->first_parameter;
    display_text_number_field_zero(requirements->first_thresholds[level]);
    text = display_scene_lookup_text(first_parameter + 273);
    scene_row24_selection_draw_lines(&tile, 85, &y, text);
    requirements = g_scene_contact_resources[
        g_scene_row24_selection_value_permutation[g_scene_request.scene]].fields.requirements;
    second_parameter = requirements->second_parameter;
    display_text_number_field_zero(requirements->second_thresholds[level]);
    text = display_scene_lookup_text(second_parameter + 273);
    scene_row24_selection_draw_lines(&tile, 85, &y, text);
    display_text_number_field_zero(g_scene_contact_resources[
        g_scene_row24_selection_value_permutation[g_scene_request.scene]].fields.costs[level]);
    text = display_scene_lookup_text(279);
    scene_row24_selection_draw_lines(&tile, 85, &y, text);
    text = display_scene_lookup_text(
            g_scene_row24_selection_descriptor_text_ids[g_scene_request.scene]);
    scene_row24_selection_draw_lines(&tile, 85, &y, text);
    display_text_select_font(3, 0, 0);
}
