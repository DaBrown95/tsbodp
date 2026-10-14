#include "input.h"
#include "scene_contact_menu.h"

void scene_contact_show_completion(void)
{
    unsigned short zero;
    unsigned int resource_address;
    const char *text;
    unsigned int tile;

    g_scene_contact_state->flags |= 16;
    zero = 0;
    resource_bios_swi_0b(&zero, (void *)0x06000000, 0x01008000);
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_configure_tile_allocation(0);
    g_input_pressed[0] = 0;
    scene_contact_prepare_backdrop();
    display_show_background(1, g_scene_contact_completion_background_control1);
    resource_address = (unsigned int)g_scene_contact_resources;
    {
        unsigned int offset = g_scene_contact_state->scene * 32;
        unsigned int field = resource_address + 4;
        const struct BackgroundResource *background =
            *(const struct BackgroundResource *const *)(offset + field);
        display_load_background(1, background, 0, 0, 0, 0);
    }
    display_text_select_font(3, 0, -1);
    text = display_scene_lookup_text(0x1869);
    tile = display_text_draw_line(1, 176, 12, text, 1);
    display_text_select_font(2, 0, -1);
    {
        unsigned int offset = (g_scene_contact_state->option + 1) * 2;
        offset += g_scene_contact_state->scene * 32;
        resource_address += 20;
        text = display_scene_lookup_text(
            *(const unsigned short *)(offset + resource_address));
    }
    display_text_copy_field_zero(text);
    text = display_scene_lookup_text(0x186a);
    display_text_draw_block(tile, 176, 32, 96, 64, &text, 1);
    audio_play_sequence_notification(54);
}
