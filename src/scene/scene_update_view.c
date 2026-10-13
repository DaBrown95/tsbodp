#include "save_world_view_update.h"

static inline unsigned int transition_row_ready(unsigned int index,
                                                unsigned int eight_index)
{
    struct SaveWorldTransitionRow *table;
    unsigned int offset;
    table = g_save_world_transition_rows;
    offset = (eight_index << 3) - (index << 3);
    return ((struct SaveWorldTransitionRow *)((unsigned int)table + offset))->ready;
}

void scene_update_view(unsigned int index)
{
    char text[20];
    unsigned int eight_index;
    unsigned int transition_eight_index;
    unsigned int *flags;
    {
        unsigned int address;
        unsigned int offset;
        address = (unsigned int)g_save_world_transition_rows;
        eight_index = index << 3;
        offset = (eight_index - index) << 3;
        address += 4;
        flags = (unsigned int *)(offset + address);
    }
    if (*flags & 0x400000) save_world_refresh_row_palette(index);
    if (*flags & 2) {
        *flags &= ~2u;
        display_fill_background_constant_rectangle(0, 25, 1, 6, 1, 0x2169);
        display_text_select_font(0, 0, -1);
        display_text_format_number(g_save_world_init_state.prefix.unknown04, text);
        display_text_copy_field_zero(text);
        display_text_draw_line(500, 236, 9, display_scene_lookup_text(6220), 2);
    }
    if (*flags & 1) {
        *flags &= ~1u;
        display_fill_background_constant_rectangle(0, 25, 0, 6, 1, 0x2169);
        display_text_select_font(0, 0, -1);
        display_time_format(&g_display_world_clock, text, 6225);
        display_text_draw_line(438, 236, 1, text, 2);
    }
    if (*flags & 0x800000) {
        save_world_show_notice(234);
        *flags &= ~0x800000u;
        transition_eight_index = eight_index;
    } else if (*flags & 0x40000) {
        save_world_show_row_flag_notice(index);
        *flags &= ~0x40000u;
        transition_eight_index = eight_index;
    } else if (*flags & 0x180000) {
        save_world_show_row_notice(index);
        *flags &= ~0x180000u;
        transition_eight_index = eight_index;
    } else if (*flags & 0x200000) {
        save_world_show_notice(292);
        *flags &= ~0x200000u;
        transition_eight_index = eight_index;
    } else {
        struct SaveWorldInitState *root;
        struct SaveWorldInitState *world;
        register unsigned char *initial asm("r0");
        register unsigned int loaded asm("r2");
        unsigned int guard_value;
        root = &g_save_world_init_state;
        initial = &root->pending_columns;
        loaded = *initial;
        guard_value = loaded;
        world = root;
        if (guard_value) {
            register unsigned int available asm("r1");
            unsigned char *column_flags;
            unsigned int i;
            unsigned int bit_base;
            i = 0;
            transition_eight_index = eight_index;
            bit_base = 1;
            column_flags = initial;
            available = loaded;
            do {
                unsigned char bit = bit_base << i;
                if (bit & available) {
                    audio_play_sequence_notification(58);
                    save_world_show_pending_column(world->pending_row, i);
                    {
                        register unsigned char *address asm("r1");
                        address = column_flags;
                        *address &= ~bit;
                    }
                    break;
                }
                ++i;
            } while (i <= 5);
        } else {
            register unsigned char *pending asm("r8");
            unsigned char pending_value;
            {
                register unsigned short offset asm("r2");
                unsigned char *address;
                offset = (unsigned int)&((struct SaveWorldInitState *)0)->prefix.unknown748 / 8;
                address = (unsigned char *)((offset << 3) + (unsigned int)root);
                pending = address;
                pending_value = *address;
            }
            transition_eight_index = eight_index;
            if (pending_value) {
                audio_play_animation_cue(38);
                save_world_show_pending_event();
                *pending = guard_value;
            }
        }
    }
    if (g_save_world_init_state.unknown750) {
        unsigned int clear_value;
        unsigned short *message_address;
        unsigned int message;
        message_address = &g_actor_scene_result_id.id;
        clear_value = 0;
        message = 309;
        *message_address = message;
        audio_play_sequence_notification(55);
        frame_activate_actor_scene_request();
        g_save_world_init_state.unknown750 = clear_value;
    }
    display_text_select_font(1, 0, -1);
    {
        register struct SaveWorldTransitionRow *table asm("r1");
        register unsigned int row_address asm("r2");
        unsigned int ticks;
        register unsigned int row_offset asm("r0");
        table = g_save_world_transition_rows;
        row_offset = (transition_eight_index - index) << 3;
        row_address = row_offset + (unsigned int)table;
        ticks = ((struct SaveWorldTransitionRow *)row_address)->ticks;
        if (ticks) {
            --ticks;
            ((struct SaveWorldTransitionRow *)row_address)->ticks = ticks;
            if (!(unsigned short)ticks) {
                register unsigned int ready asm("r1");
                ready = ((struct SaveWorldTransitionRow *)row_address)->ready;
                if (!ready)
                    display_fill_background_constant_rectangle(0, 5, 15, 25, 5, ready);
            }
        }
    }
    {
        if (index == g_scene_primary_views.current_view && !(g_game_flags & 0x100000)) {
            switch (transition_row_ready(index, transition_eight_index)) {
            case 1:
                if ((g_input_pressed[index] & 0x200) &&
                    (g_scene_primary_views.slots[index].object->state == 16 ||
                     g_scene_primary_views.slots[index].object->state == 27))
                    save_world_begin_transition(index);
                save_world_update_row_gauges();
                break;
            case 0:
                if ((g_input_pressed[index] & 0x200) &&
                    (g_scene_primary_views.slots[index].object->state == 16 ||
                     g_scene_primary_views.slots[index].object->state == 27)) {
                    save_world_finish_transition(index, 0);
                    audio_play_animation_cue(12);
                }
                break;
            }
        }
    }
    {
        unsigned char average = frame_actor_need_average(
            (struct FrameActorNeedState *)g_frame_actor_local_need_state);
        unsigned int gauge = save_world_scale_gauge(average, 100, 7);
        g_save_world_summary_map = display_load_background_resource_dma(
            0, g_save_world_need_resources[gauge], 492);
    }
}
