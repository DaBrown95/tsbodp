#include "display_menu_results.h"

void display_menu_stage_result_text(const char *text)
{
    if (text) {
        display_disable_window(0);
        display_enable_window(1);
        display_text_set_background_control(g_display_menu_control1);
        display_text_select_font(3, 3, -1);
        display_text_set_line_height(12);
        display_text_draw_block(452, 72, 116, 144, 36, &text, 0);
        display_text_set_background_control(g_display_menu_control0);
    } else
        display_menu_prepare_primary();
}

asm(".align 2, 0");
