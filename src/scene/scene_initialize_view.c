#include "save_world_view_initialization.h"

/* Keep the final row lookup independent of the earlier mode-dependent store. */
static inline unsigned int scene_initialized_row_index(unsigned int index)
{
    register unsigned int value asm("r1");
    value = index;
    return value;
}

static inline unsigned int *scene_initialized_row_flags(unsigned int base,
    unsigned int offset)
{
    unsigned int address;
    address = base;
    address += 4;
    return (unsigned int *)(offset + address);
}

void scene_initialize_view(unsigned int index, unsigned int mode)
{
    unsigned int saved_index;
    unsigned int limited_mode;
    unsigned int eight_index;
    saved_index = index;
    limited_mode = (unsigned char)mode;
    if (!limited_mode) save_world_refresh_row_palette(saved_index);
    {
        unsigned int selection_address = (unsigned int)&g_scene_primary_views;
        selection_address += 0x31;
        eight_index = saved_index << 3;
        if (saved_index == *(unsigned char *)selection_address) {
            unsigned int i = 0;
            unsigned int base = (unsigned int)g_save_world_transition_rows;
            unsigned int offset = (eight_index - saved_index) << 3;
            unsigned char *value;
            const unsigned short *map;
            base += 0x30;
            value = (unsigned char *)(offset + base);
            do {
                *value = frame_actor_need_value(
                    (struct FrameActorNeedState *)g_frame_actor_local_need_state, i);
                ++value;
                ++i;
            } while (i <= 7);
            display_fill_background(0, 0);
            scene_view_original_3aff0(0, 0, 16, 368, 0,
                (unsigned char *)&g_save_world_init_state + 0x20);
            scene_view_original_34630(0, 428, 2);
            map = display_load_background_resource_dma(0, &g_save_world_view_background_a, 54);
            g_save_world_gauge_map = (const struct DisplayStoredMap *)map;
            g_save_world_transition_map = display_load_background_resource_dma(
                0, &g_save_world_row_palette_a, 1);
            g_save_world_summary_map = display_load_background_resource_dma(
                0, &g_save_world_view_background_c, 492);
            display_fill_background_rectangle(0, 0, 15, 4, 1, 0x11ec);
            display_fill_background_rectangle(0, 4, 16, 1, 4, 0x11f0);
            display_load_background_resource_dma(0, &g_save_world_view_background_d, 437);
            display_fill_background_constant_rectangle(0, 4, 15, 1, 1, 0x11b5);
            display_load_background_dma(0, &g_save_world_view_background_e, 360, 2, 24, 0);
        }
    }
    if (limited_mode) {
        unsigned int base = (unsigned int)g_save_world_transition_rows;
        unsigned int offset = (eight_index - saved_index) << 3;
        base += 4;
        *(unsigned int *)(offset + base) = ~0u;
    }
    display_text_set_background_control(g_scene_background_control0);
    display_text_select_font(1, 0, -1);
    {
        register unsigned int base asm("r6");
        unsigned int offset;
        unsigned int *row;
        unsigned int ready;
        base = (unsigned int)g_save_world_transition_rows;
        offset = (eight_index - scene_initialized_row_index(saved_index)) << 3;
        row = (unsigned int *)(offset + base);
        ready = *row;
        if (ready == 1) {
            save_world_finish_transition(saved_index, 1);
            *scene_initialized_row_flags(base, offset) |= 0x3fc;
            save_world_update_row_gauges();
            *row = ready;
        }
        {
            register unsigned int *flags asm("r0");
            flags = scene_initialized_row_flags(base, offset);
            *flags |= 3;
        }
    }
}
