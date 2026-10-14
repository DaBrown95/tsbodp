#include "input.h"
#include "scene_contact_menu.h"
void scene_contact_start_activity(void)
{
    unsigned short zero;
    {
        unsigned short *source;
        source = &zero;
        *source = 0;
    }
    resource_bios_swi_0b(&zero, (void *)0x06000000, 0x01008000);
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_configure_tile_allocation(0);
    g_input_pressed[0] = 0;
    if (g_scene_contact_state->scene <= 1)
        scene_contact_original_initialize_primary();
    else
        scene_contact_original_initialize_secondary();
    if (g_scene_contact_state->scene != 6)
        audio_select_sequence(g_scene_contact_definitions[g_scene_contact_state->scene].sequence);
    g_scene_contact_state->flags |= 12;
    display_time_update_scene_countdown();
    scene_contact_refresh_value();
    transition_run_first(63, 0);
    if (g_scene_contact_state->scene <= 1) {
        if (g_scene_contact_state->scene == 1) {
            transition_configure_alpha(2, 20);
            transition_set_alpha(4, 12);
        } else
            background_animation_configure_alpha();
    }
}
