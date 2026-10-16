#include "scene_link_entry_quantities.h"

void scene_link_entry_draw_quantities(void)
{
    unsigned int count;
    unsigned char i;

    display_text_select_font(0, 0, 0);
    for (i = 0; i < g_link_received_join.metadata[0]; ++i) {
        unsigned char y;
        unsigned int x;
        unsigned int next_y;
        unsigned int next_x;
        unsigned int remainder;
        unsigned int slot_index;
        struct FrameObject **objects;
        struct FrameObject **slot;
        struct FrameObject *object;
        const char *text;

        count = g_link_entry_offers.records[i].count;
        y = g_scene_link_entry_captions[i].y - (count >> 3);
        x = g_scene_link_entry_captions[i].x;
        next_y = y + 1;

        display_fill_background_constant_rectangle(1, x, next_y, 1, (count >> 3),
            (unsigned short)((unsigned int)((i + 3) << 12) | 17));
        next_x = x + 1;
        display_fill_background_constant_rectangle(1, next_x, next_y, 1,
            (count >> 3), (unsigned short)((unsigned int)((i + 3) << 12) | 18));
        display_fill_background_constant_rectangle(1, x, y, 1, 1,
            (unsigned short)((unsigned int)((i + 3) << 12) | ((remainder = count & 7) * 2 + 1)));
        display_fill_background_constant_rectangle(1, next_x, y, 1, 1,
            (unsigned short)((unsigned int)((i + 3) << 12) | (remainder * 2 + 2)));
        display_fill_background_constant_rectangle(1, x, y - 1, 2, 1, 0);
        display_text_number_field_zero((int)(
            ((unsigned int)g_link_entry_offers.multiplier * count +
             (unsigned int)g_link_entry_offers.records[i].cost) >> 16));
        objects = g_display_scene_frame_objects;
        slot_index = i + 6;
        slot = &objects[slot_index];
        object = *slot;
        text = display_scene_lookup_text(0x184c);
        display_text_set_object_string(object, text);
        y = (unsigned char)(y * 8 - remainder);
        frame_set_centered_integer_position(*slot, (short)(next_x * 8),
            (short)(y - 2));
    }
    display_text_set_background_control(g_scene_link_entry_text_control);
}
