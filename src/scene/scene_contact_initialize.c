#include "input.h"
#include "scene_contact_menu.h"

/* Scope the real fill-source store before the BIOS transfer. */
static inline void initialize_fill(unsigned short *output)
{
    *output = 0;
}

void scene_contact_initialize(void)
{
    unsigned short zero;
    unsigned int control, tile;
    const char *text;
    unsigned int resource_address;

    initialize_fill(&zero);
    resource_bios_swi_0b(&zero, (void *)0x06000000, 0x01008000);
    display_set_mode(0);
    display_enable_layers(0x1000);
    display_configure_tile_allocation(0);
    g_scene_contact_state = heap_allocate_zeroed(420);
    g_scene_contact_state->scene = g_scene_request.mode;
    g_scene_contact_state->option = g_scene_request.scene;
    g_scene_contact_state->phase = 0;
    g_input_pressed[0] = 0;
    display_show_background(1, g_scene_contact_initial_background_control1);
    resource_address = (unsigned int)g_scene_contact_resources;
    {
        unsigned int offset = g_scene_contact_state->scene * 32;
        const struct BackgroundResource *background =
            *(const struct BackgroundResource *const *)(offset + resource_address);
        display_load_background(1, background, 0, 1, 0, 0);
    }
    control = g_scene_contact_initial_text_control;
    display_show_background(0, control);
    display_fill_background(0, 0);
    display_load_resource_palette(&g_scene_contact_palette_resource, 0);
    display_text_set_background_control(control);
    display_load_palette_ranges(&g_scene_contact_palette_ranges);
    display_text_select_font(3, 6, -1);
    text = display_scene_lookup_text(g_scene_contact_state->scene + 0x1859);
    tile = display_text_draw_line(1, 120, 8, text, 1);
    display_text_select_font(2, 0, -1);
    {
        unsigned int offset = g_scene_contact_state->option * 2;
        offset += g_scene_contact_state->scene * 32;
        resource_address += 20;
        text = display_scene_lookup_text(
            *(const unsigned short *)(offset + resource_address));
    }
    tile = display_text_draw_line(tile, 120, 24, text, 1);
    display_text_select_font(2, 3, -1);
    text = display_scene_lookup_text(g_scene_contact_state->scene + 0x1861);
    tile = display_text_draw_block(tile, 8, 40, 224, 32, &text, 0);
    display_text_draw_block(tile, 8, 72, 128, 88, &text, 0);
    transition_run_first(63, 0);
    if (g_scene_previous_request.unknown_00 == 10) {
        g_scene_contact_state->return_mode = 1;
        g_scene_contact_input_setup.handler = scene_contact_handle_input_notice;
    } else {
        g_scene_contact_state->return_mode = 0;
    }
}

/* The original section ends with two zero alignment bytes. */
asm(".align 2,0");
