#include "display_catalog_presentation.h"
#include "display_scene_setup.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"
void display_catalog_draw_selection(void)
{
    display_fill_background_constant_rectangle(1, 1, 12, 28, 8, 0);
    display_text_select_font(3, 0, -1);
    display_text_set_line_height(12);
    if (g_display_scene_request_state.scene > 4) {
        struct DisplayCatalogState *catalog = &g_display_catalog_state;
        struct DisplayCatalogType *types = catalog->context->types;
        unsigned int index = g_display_scene_request_state.scene - 5;
        if (types[g_display_scene_request_state.scene - 5].unknown_00[0] != 255) {
            display_catalog_draw_name(166, 120, 96,
                types[g_display_scene_request_state.scene - 5].unknown_00[0], index, 1);
            display_text_select_font(1, 0, -1);
            display_catalog_draw_details(226, 8, 112, 224,
                types[g_display_scene_request_state.scene - 5].unknown_00[0], index, 0);
        }
        if ((unsigned char)(types[g_display_scene_request_state.scene - 5].unknown_00[0] + 0x55) <= 0x17) {
            /* A separate observed byte beyond the partial context view. */
            unsigned int address = (unsigned int)catalog;
            unsigned int label = *(unsigned char *)(address + 0x41a);
            display_text_copy_field_zero(display_scene_lookup_text(label + 0x1789));
            display_text_draw_line(476, 120, 144,
                                  display_scene_lookup_text(298), 1);
        }
    } else {
        const char *text = display_scene_lookup_text(g_display_scene_request_state.scene + 504);
        display_text_draw_line(166, 120, 96, text, 1);
        display_text_select_font(1, 0, -1);
        display_text_draw_all_lines(226, 8, 112, 224,
            display_scene_lookup_text(g_display_scene_request_state.scene + 795), 0);
    }
}
asm(".align 2, 0");
