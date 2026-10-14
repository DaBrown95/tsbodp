#include "scene_text_bank.h"
void scene_text_bank_create_row(unsigned int row)
{
    unsigned int color;
    unsigned int offset;
    const char *text;
    if (row != g_scene_request.parameter) {
        color = 0;
        offset = 65535;
    } else {
        color = 3;
        offset = 0;
    }
    display_text_select_font(3, color, 0);
    text = display_scene_lookup_text(row + 6);
    display_create_text_slot(&text, row);
    frame_set_centered_integer_position(g_display_text_slots[row], 120,
                                        (short)(row * 16 + 32 + offset));
}
asm(".align 2,0");
